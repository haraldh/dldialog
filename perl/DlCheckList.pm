#!/usr/bin/perl
####################################################
#						   #
# File:		DlCheckList.pm  	           #
#

package DlCheckList;

####################################################
#
# Konstruktor new: legt ein neues  DlCheckList-Objekt an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Titel: Titel der CheckList
# Var: Name der Variablen, die die gewählten CheckButton zurückgibt. 
# Höhe, Breite: Geometrie der Box (tut in dldialog noch net)

sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my ( $title, $var, $height, $width) = @_;
    
    if ($title) { $self->{_title} = $title;}
    if ($var) {
      if ($var=~/=/) {      # '=' im Variablennamen führt zu ParseError
	($var, $value) = split /=/ , $var;    # trennen
	if ($value) { $self->{_value} =$value}  #und Wert merken
      }
      $self->{_var} = $var;}
    if ($height) { $self->{_height} =$height}
    if ($width) { $self->{_width} =$width}

    # und Referenz zurückgeben
    bless($self, $class);
    return $self;
}

sub getTitle {
  my $self = shift;
  my $title = $self->{_title};
  return $title;
}

sub setTitle {
  my ($self, $title) = @_;
  my $oldtitle = $self->getTitle();
  $self->{_title} = $title;
  return $oldtitle;
}
  
sub setText {
  my ($self, $text, $pos) = @_;
  if ($pos=~/^b/i) {$self->{_btext}=$text}
  else {$self->{_text}=$text}
}


sub insertButton {
  my $self = shift;
  push @{$self->{_buttons}} , @_;
  return $#{$self->{_buttons}}+1;
}
  

sub removeButton {
  my $self = shift;
  my $buttonnr = shift;
  if ($buttonnr <= 0) {return}
  $buttonnr--;
  my $i = 0;
  my @WStack=();
  foreach $button (@{$self->{_buttons}}) {
    unless ($i eq $buttonnr) {push @WStack, $button}
    $i++;
  }
  @{$self->{_buttons}}=@WStack;
  return $#{$self->{_buttons}}+1;
}



sub getCode {
  my $self = shift;
  my $code="";
  if($self->{_text}) { $code.=" text \"$self->{_text}\" "}
  if ($self->{_value}) { $code .=" $self->{_var}=\"$self->{_value}\"; "}
  $code.=" checklist \"$self->{_title}\" ";
  if ($self->{_var}) { $code.=" -var $self->{_var} " }
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  $code.=" { ";

  foreach $button (@{$self->{_buttons}}) { $code.="checkbutton \"$button\"; " }

  $code .=" }";
  if($self->{_btext}) { $code.=" text \"$self->{_btext}\"; "}
  return $code;
}


1; # Keep require happy

