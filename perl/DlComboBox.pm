#!/usr/bin/perl
####################################################
#						   #
# File:		DlComboBox.pm  	                   #
#

package DlComboBox;

####################################################
#
# Konstruktor new: legt ein neues  DlComboBox-Objekt an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Titel: Titel der ComboBox
# Var: Name der Variablen, die den/die gewählten Items zurückgibt. 
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
  if ($pos=~/^[br]/i) {$self->{_btext}=$text}
  else {$self->{_text}=$text};
  $self->{_textpos}=$pos;
}

sub insertItem {
  my $self = shift;
#  print "DlC:@_\n";
  push @{$self->{_items}} , @_;
  return $#{$self->{_items}}+1;
}

sub getItem {
  my $self = shift;
  my $itemnr = shift;
  return ${$self->{_items}}[$itemnr-1];
}

sub clearItems {
  my $self = shift;
  @{$self->{_items}}=();
  return}

sub removeItem {
  my $self = shift;
  my $itemnr = shift;
  if ($itemnr <= 0) {return}
  $itemnr--;
  my $i = 0;
  my @WStack=();
  foreach $item (@{$self->{_items}}) {
    unless ($i eq $itemnr) {push @WStack, $item}
    $i++;
  }
  @{$self->{_items}}=@WStack;
  return $#{$self->{_items}}+1;
}


sub getCode {
  my $self = shift;
  if ($self->{_textpos} =~ /^[lr]/i) { $code = "row ";}
  else { $code = "col ";}
  $code.=" \"$self->{_title}\" {";
  if ($self->{_text}) { $code.=" text \"$self->{_text}\"; "}
  if ($self->{_value}) { $code .=" $self->{_var}=\"$self->{_value}\"; "}
  $code.=" combobox  ";
  if ($self->{_var}) { $code.=" -var $self->{_var} " }
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  $code.=" { ";
  foreach $item (@{$self->{_items}}) { $code.="comboitem \"$item\" ; " }
  $code .=" }";
  if($self->{_btext}) { $code.=" text \"$self->{_btext}\"; "}
  $code .=" }";
  return $code;
}


1; # Keep require happy

