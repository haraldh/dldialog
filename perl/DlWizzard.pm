#!/usr/bin/perl -w
####################################################
#						   #
# File:		DlWizzard.pm   		           #
# Authors:	Thomas Hagedorn                    #
#                                                  #
package DlWizzard;
use strict;
use Cwd;
use DlDialog;


sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    @{$self->{stack}} = ();
    @{$self->{hidelist}} = ();
    @{$self->{callback}} = ();
    $self->{_islast} = 0;
    $self->{isfirst} = 0;
    my ($package, $file, $line) = caller();
    # Uebergebene oder ermittelte Attribute merken
    my $title = shift;
    $title = "TurboDialog" unless $title;
    $self->{_dialogtitle}    = $title;
    $self->{_caller_package} = $package;
    bless($self, $class);
    return $self;
}
 
sub store {
  my $self = shift;
  my $dialog = shift;
  my $title = $dialog->getTitle();
  my @stack = @{$self->{stack}};
  my $stacksize = @stack;
  push @stack, $dialog;
  $self->{callback}[$stacksize] = shift;
  $self->{_islast} = @stack;
  @{$self->{stack}} = @stack;
  return $self->{_islast};
}

sub setHelp {
  my $self = shift;
  my $helpfile = shift;
  $helpfile =~ s/^~/$ENV{HOME}/;
  my $rundir = `pwd`;
  chomp $rundir;
  $helpfile =~ s/^\./$rundir/;
  $self->{helpfile} = new DlHelp($helpfile);
}

sub skip {
  my $self = shift;
  my $number = shift;
  my $stacksize = $self->{stack};
  my $pos = $self->{stackpos} + $number;
#  print "Old position is $self->{stackpos}: Now we should have Pos $pos from $stacksize, scipped $number\n";
  if ($pos < 0) {$pos = 0}
  if ($pos > $stacksize) {$pos = $stacksize}
  $self->{stackpos} = $pos;
  return $pos;
}

sub hide {
  my $self = shift;
  my @numbers = @_;
  my $number;
  my $islast = $self->{_islast};
  my $stacksize = $self->{stack};
  foreach $number (@numbers) {
    $number--;
    if ($number > $stacksize) { next }
    if ($number < $self->{isfirst}) { next }
    $self->{hidelist}[$number] = 1;
    if ($islast-1 eq $number) {
      while ($self->{hidelist}[$islast-1] eq 1) { $islast-- }
    }
    elsif ($self->{isfirst} eq $number) {
      while ($self->{hidelist}[$self->{isfirst}] eq 1) { $self->{isfirst}++ }
    }
  }
  $self->{_islast} = $islast;
}

sub unhide {
  my $self = shift;
  my $islast = $self->{_islast};
  my @numbers = @_;
  my $number;
  my $stacksize = $self->{stack};
  foreach $number (@numbers) {
    $number--;
    next  if $number > $stacksize;
    next if $number < 0;
    $self->{hidelist}[$number] = 0;
    if ($number < $self->{isfirst}) {$self->{isfirst} = $number}
    $number++;
    if ($number > $islast) {$islast = $number}
  }
  $self->{_islast} = $islast;
}


sub proceed {
  my $self = shift;
  my $islast;
  $self->{stackpos} = 0;
  my ($result,$dialog,$callback);
  my $final = $self->{stack};
  $final--;

###################################################################
# Main loop
#
  for (;;) {
    $result = "";
  $islast = $self->{_islast};
# auf verborgene Dialoge achten
    if ($self->{hidelist}[$self->{stackpos}]) {
      if ($dialog->{result} eq $dialog->{back}) {
#	print "went back with stackpos $self->{stackpos}, isfirst $self->{isfirst}\n";
	if ($self->{stackpos} < $self->{isfirst}) {$self->{stackpos}=+2}
	unless ($self->{stackpos}<0) {$self->{stackpos}--}
      }
      else {
	unless ($self->{stackpos} eq $final) {$self->{stackpos}++}
      }
      next
    }
# Dialog initiieren
    $dialog = $self->{stack}[$self->{stackpos}];
    $callback = $self->{callback}[$self->{stackpos}];             
    $dialog->setHelpWidget($self->{helpfile});
# Buttons inteligent aufbauen
    if ($self->{stackpos} eq $self->{isfirst}) {$result=$dialog->show('start')}
    elsif ($self->{stackpos} eq $islast-1) {$result=$dialog->show('end')}
    else {$result=$dialog->show('wizzard')}
# Rückgabezustand prüfen
    if ($result) {
      if ($result eq 'next') {$self->{stackpos}++; $result = 'next'}
      if ($result eq 'back') {$self->{stackpos}--; $result = 'back'}
      if ($result eq 'cancel') {$result = 'cancel'}
      if ($result eq 'ok') {$self->{stackpos}++; $result = 'ok'}
#      print "Result is $result\n";
    }
# Callback aufrufen
    &$callback;
    if (($result eq 'cancel') || ($result eq 'ok')) { return $result }   #Ende
  }
}

1;
    
