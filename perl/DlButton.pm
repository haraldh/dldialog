#!/usr/bin/perl
####################################################
#						   #
# File:		DlButton.pm  	                   #
#

package DlButton;

####################################################
#
# Konstruktor new: legt einen neue  DlButton an und gibt
# die Referenz darauf zurück.

sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    $self->{_title} = shift;
    $self->{_var} = shift;
    $self->{_font} = shift;
    $self->{_fsize} = shift;
    $self->{_fcolor} = shift,

    bless($self, $class);
    return $self;
}
 
sub getCode {
  my $self = shift;
  my $code="";
  $code.="button \"$self->{_title}\" ";
  if ($self->{_var}) { $code.=" -var $self->{_var} -set \"1\"" };
  if ($self->{_font}) {
    $code.=" -font $self->{_font}";
    if ($self->{_fsize}) {
      $code.=" -size $self->{_fsize}";
    }
    if ($self->{_fcolor}) {
      $code.=" -fg $self->{_fcolor}";
    }
  }
  $code.=" -exit; ";
  return $code;  
}



1; # Keep require happy
