#!/usr/bin/perl
####################################################
#						   #
# File:		DlList.pm  	                   #
#

package DlList;

####################################################
#
# Konstruktor new: legt ein neues  DlList-Objekt an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Titel: Titel der Liste
# Var: Name der Variablen, die den/die gewählten Items zurückgibt. 
# Multi (m|multi|mehrere): Multiple Choice möglich
# Exit (t|true|y|yes|j|ja): Listitem reagiert auf Doppelclick
# Breite, Höhe: Geometrie der Box in Prozent des Serverwindows

sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my ( $title, $var, $multi, $exit, $width, $height) = @_;
    
    if ($title) { $self->{_title} = $title;}
    if ($var) {
      if ($var=~/=/) {      # '=' im Variablennamen führt zu ParseError
	($var, $value) = split /=/ , $var;    # trennen
	if ($value) { $self->{_value} =$value}  #und Wert merken
      }
      $self->{_var} = $var;}
    if ($multi) { $self->{_multi} = 'true'}
    if ($exit=~/^[tjy]/i) {$self->{_exit} = $exit}
    if ($height) { $self->{_height} =$height}
    if ($width) { $self->{_width} =$width}

    # und Referenz zurückgeben
    bless($self, $class);
    return $self;
}

sub setFont {
  my $self = shift;
  my ($index, $font) = @_;
  unless ($font) {
    $self->{_font} = $index;
    return
  }
  return if $index <= 0;
  $self->{_ifont}[$index-1] = $font;
}

sub setFontSize {
  my $self = shift;
  my ($index, $size) = @_;
  unless ($size) {
    $self->{_fsize} = $index;
    $self->{_font} = 'normal' unless $self->{_font};
    return
  }
  return if $index <= 0;
  $self->{_ifsize}[$index-1] = $size;
  $self->{_ifont}[$index-1] = 'normal' unless $self->{_ifont}[$index-1];
}

sub setColor {
  my $self = shift;
  my ($index, $color) = @_;
  unless ($color) {
    $self->{_fcolor} = $index;
    $self->{_font} = 'normal' unless $self->{_font};
    return
  }
  return if $index <= 0;
  $self->{_ifcolor}[$index-1] = $color;
  $self->{_ifont}[$index-1] = 'normal' unless $self->{_ifont}[$index-1];
}

sub setImage {
  my $self = shift;
  my ($index, $image) = @_;
  return if $index <= 0;
  $self->{_images}[$index-1] = $image;
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
  
sub getList {
  # gibt eine Referenz auf ein Array zurück
  my $self = shift;
  return $self->{_items};
}

sub setText {
  my ($self, $text, $pos) = @_;
  if ($pos=~/^b/i) {$self->{_btext}=$text}
  else {$self->{_text}=$text}
}

sub insertItem {
  my $self = shift;
  push @{$self->{_items}} , @_;
  return $#{$self->{_items}}+1;
}
 
sub getItem {
    my $self = shift;
    my $itemnr = shift;
    return ${$self->{_items}}[$itemnr-1];
}

sub removeItem {
  my $self = shift;
  my $itemnr = shift;
  if ($itemnr <= 0) {return}
  $itemnr--;
  my $i = 0;
  my @WStack=();
  my $giveback = ${$self->{_items}}[$itemnr];
  foreach $item (@{$self->{_items}}) {
    unless ($i eq $itemnr) {push @WStack, $item}
    $i++;
  }
  @{$self->{_items}}=@WStack;
# gib den entfernten Eintrag zurück
  return $giveback;
}

sub clear {
  my $self = shift;
  @{$self->{_items}} = ();
}


sub getCode {
  my $self = shift;
  my $count = 0;
  my $code="col \"$self->{_title}\" {";
  if($self->{_text}) { $code.=" text \"$self->{_text}\" ;"}
  if ($self->{_value}) { $code .=" $self->{_var}=\"$self->{_value}\"; "}
  $code.=" list ";
  if ($self->{_var}) { $code.=" -var $self->{_var} " }
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  if ($self->{_multi}) { $code.=" -multi " }
  if ($self->{_font}) { 
    $code.=" -font $self->{_font}";
    if ($self->{_fsize}) { $code.=" -size $self->{_fsize}"}
    if ($self->{_fcolor}) { $code.=" -fg \"$self->{_fcolor}\""}
  }
  $code.=" { ";

  foreach $item (@{$self->{_items}}) { 
    $code.="listitem \"$item\" "; 
    $self->{_ifont}[$count] = $self->{_ifont}[$count] || $self->{_font};
    $self->{_ifsize}[$count] = $self->{_ifsize}[$count] || $self->{_fsize};
    $self->{_ifcolor}[$count] = $self->{_ifcolor}[$count] || $self->{_fcolor};

    if ($self->{_ifont}[$count]) {
      $code.=" -font $self->{_ifont}[$count]";
      if ($self->{_ifsize}[$count]) { $code.=" -size $self->{_ifsize}[$count]"}
      if ($self->{_ifcolor}[$count]) { $code.=" -fg $self->{_ifcolor}[$count]"}
    }
    if ($self->{_images}[$count]) { 
      $code .= " -image \"$self->{_images}[$count]\"";
    }
    if ($self->{_exit}) {$code.=" -exit "}
    $code .=";";
    $count++;  
  }
  $code .=" }";

  if($self->{_btext}) { $code.=" text \"$self->{_btext}\"; "}
  $code.=" }";
#  print "DlList.code is $code\n";
  return $code;
}


1; # Keep require happy

