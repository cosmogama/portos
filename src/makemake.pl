#! /usr/bin/perl

#### BUILD MAKEFILE ####

use strict;

## SETTINGS ##

my $CC="i586-elf-gcc";
my $CFLAGS_NEEDED_FOR_DEPENDENCY_BUILDING="-nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ffreestanding";

my $IDIR="-I kernel -I fs -I test";

my $MAIN_C="kernel/kernel.c";

my $ODIR="obj";

my %ASM_DEPENDENCIES = ( 
	'kernel/interrupts.c' => ['kernel/isr_stubs.s'] , 
	'kernel/idt.c' => ['kernel/isr_stubs.s' , 'kernel/idt-asm.s'] 
);

## CONSTANTS ##
my $FILENAME_CHARS='[^\s\\\/]';

## GLOBAL ##
my %marked;

## START ##

# open Makefile for writing
open( MAKEFILE , '>rules.mk' ) or die "ERROR: Can't open Makefile for writing";

finddeps($MAIN_C);

close( MAKEFILE );

## FUNCTIONS ##

sub filter_out_h_files{
	my $makerule = shift;
	my @deps = split( / / , $makerule );
	my $target = shift @deps;
	my $src_dep = shift @deps;

	# filter out h file if it is the header for the target
	my $target_wno_ext = $target;
	$target_wno_ext =~ s/\..://;
	my $num_dep = $#deps+1;
	for( my $i=0; $i<$num_dep; $i++ ){
		if( $deps[$i] =~ m/$target_wno_ext\.h/ ){
#			print "removing !$deps[$i]!\n";
			@deps = @deps[0..$i-1,$i+1..$#deps];
			$num_dep--;
			last;
		}
	}

	# filter out h files that have no source counterpart
	my $check;
	for( my $i=0; $i<$num_dep; $i++ ){
#		print "checking !$deps[$i]!\n";
		if( $deps[$i] =~ m/\.h/ ){
			$check = $deps[$i];
			$check =~ s/\s+//;
			$check =~ s/\.h/\.c/;
			if( ! (-e "./$check") ){
#				print "removing !$check!\n";
				@deps = @deps[0..$i-1,$i+1..$#deps];
				$num_dep--;
				$i--;
			}
		}
	}
	$makerule = cleanup_space_at_end_of_rule( $makerule ) . "\n";
	$makerule = join( " " , $target , $src_dep , @deps );
	return $makerule;
}

sub cleanup_space_at_end_of_rule{
	my $makerule = shift;
	$makerule =~ s/[\\\s]+$//;
	return $makerule;
}

sub gen_makerule_print{
	my $makerule = shift;

	# do not modify target or targets' source
	my @deps = split( / / , $makerule );
	my $target = shift @deps;
	my $src_dep = shift @deps;
	$makerule = join " " , @deps;
	#print "makerule before replace=!$makerule!\n";

	# cause target to depend on object file targets not header or asm files
	$makerule =~ s/($FILENAME_CHARS+)\/($FILENAME_CHARS+)\.h/obj\/$2\.o/g;
	$makerule =~ s/($FILENAME_CHARS+)\/($FILENAME_CHARS+)\.s/obj\/$2\.o/g;
	#print "makerule after replace wno target or source=!$makerule!\n";

	$makerule = $target . " " . $src_dep . " " . $makerule;
	#print "makerule after replace=!$makerule!\n";
	return cleanup_space_at_end_of_rule($makerule) . "\n";
}

sub gen_makerule_parse{
	my $makerule = shift;

	# remove target and target's source file, they won't need to be checked for dependencies
	my @deps = split( / / , $makerule );
	shift @deps;
	shift @deps;
	$makerule = join( " " , @deps );

	# turn multi-lined dependencies into single line of dependencies
	$makerule =~ s/[\\\n]//g;
	$makerule =~ s/ +/ /g;
	$makerule =~ s/^ +//g;
	$makerule =~ s/ +$//g;

	# check each header files source file for dependencies
	$makerule =~ s/\.h/\.c/g;
	return $makerule;
}

sub append_asm_dependencies{
	my $makerule = shift;
	my @deps = split( / / , $makerule );
	my $targets_src = $deps[1];
	$targets_src =~ s/\n//g;
#print "checking for asm dependencies for target=!$targets_src!\n";
#	foreach my $temp (@{$ASM_DEPENDENCIES{$targets_src}}){
#		print "dep=!$temp!\n";
#	}
	if( defined @{$ASM_DEPENDENCIES{$targets_src}} ){
		$makerule = cleanup_space_at_end_of_rule( $makerule );
		$makerule = join " " , $makerule , @{$ASM_DEPENDENCIES{$targets_src}} , "\n";
#		print "rule w asm deps appended=!$makerule!\n";
	}
	return $makerule;
}

sub gen_makerule{
	my $filepath = shift;
	my $makerule;

	# let gcc tell me the dependencies 
	if( $filepath =~ m/\.c/ ){
		my $stmt = "$CC $CFLAGS_NEEDED_FOR_DEPENDENCY_BUILDING -c $filepath $IDIR -MM";
		$makerule = `$stmt`;
	}
	# gcc doesn't generate dependencies for .s files
	# have to do manually :(
	elsif( $filepath =~ m/\.s/ ){
		#
		my $target = $filepath; 
		$target =~ s/(.+)\/(.+)\.s/$2\.o/;
		$makerule = $target . ": " . $filepath . "\n";
	}
	# unrecognized source file
	else{
		print "ERROR: trying to generate dependencies on a non-source file=!$filepath!\n";
	}
	return $makerule;
}

sub finddeps{
	my $filepath = shift;

	if( $marked{$filepath} == 1 ){
		return;
	}
	$marked{$filepath} = 1;
	
	my $makerule = gen_makerule( $filepath );
	#print "orig rule=!$makerule! for file=!$filepath!\n";

	#
	$makerule = append_asm_dependencies( $makerule );

	# remove header file dependencies with no source file counterpart
	# I can do this because header files will become part of source
	# file that is including it.  Header files that have things
	# defined in counterpart source files need to have their source
	# files compiled into object files
	$makerule = filter_out_h_files($makerule);

	# put target in object directory
	$makerule =~ s/($FILENAME_CHARS+)\.o/obj\/\1\.o/;
	#print "filtered rule=!$makerule!\n";

	my $makerule_print = gen_makerule_print( $makerule );
	my $makerule_parse = gen_makerule_parse( $makerule );
	#print "mprint=!$makerule_print!\n";
	#print "mparse=!$makerule_parse!\n";

	print MAKEFILE $makerule_print;
	print MAKEFILE "\t" , '@$(CC) $(CFLAGS) -c $< -o $@ $(IDIR)' , "\n\n";

	# if no dependencies return immediately
	if( $makerule_parse eq "" ){ return; }

	# recursively find the dependencies' dependencies
	foreach my $dep (split(/ / , $makerule_parse)){
 
		# if dep is a header file, check its c file counterpart for dependencies
		if( $dep =~ m/\.c/ or $dep =~ m/\.s/ ){			
			finddeps($dep);
		}
		else{
			print "ERROR: trying to finddeps on wrong file type=!$dep!\n";
		}
	}
}
