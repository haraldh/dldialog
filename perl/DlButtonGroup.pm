#!/usr/bin/perl
####################################################
#						   #
# File:		DlButtonGroup.pm  	           #
#

package DlButtonGroup;

####################################################
#
# Konstruktor new: legt eine neue  DlButtonGroup an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Orientierung ( r|row|c|col|f|form): default 'form'
# Titel: Titel der WidgetGruppe
# Titelposition: ( t|top|b|bottom|l|left|r|right)
# Var: Name der Variablen, die den gedrückten Button zurückgibt. 
# Höhe, Breite: Geometrie der Box (tut in dldialog noch net)

sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my ($orient, $title, $titlepos, $var, $height, $width) = @_;
    if ($orient) {
        if ($orient =~ /(row|r)/i) { $self->{_orientation} = "row" }
        elsif ($orient =~ /(col|c)/i) { $self->{_orientation} = "col" }
        elsif ($orient =~ /(form|f)/i) { $self->{_orientation} = "form" }
	else { $self->{_orientation} = "form" }
	      }
    if ($title) { $self->{_title} = $title;}
    if ($titlepos) {
      if ($titlepos=~/^t/i) { $self->{_titlepos} = "top";}
      elsif ($titlepos=~/^b/i) { $self->{_titlepos} = "bottom";}
      elsif ($titlepos=~/^l/i) { $self->{_titlepos} = "left";}
      elsif ($titlepos=~/^r/i) { $self->{_titlepos} = "right";}
    }
    if ($var) { $self->{_var} = $var;}
    if ($height) { $self->{_height} =$height}
    if ($width) { $self->{_width} =$width}
 
    bless($self, $class);
    return $self;
}

 
sub insertButton {
  my $self = shift;
  push @{$self->{_buttons}} , @_;
  return $#{$self->{_buttons}}+1;
}
  
sub setImage {
  my $self = shift;
  my $nr = shift;
  my $image  =shift;
  return if (($nr <= 0) || !$image);
  $self->{_images}[$nr-1] = $image;
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


sub removeButton {
  my $self = shift;
  my $buttonnr = shift;
  if ($buttonnr <= 0) {return}
  $buttonnr--;
  my $i = 0;
  my @WStack=();
  my @IStack=();
  foreach $button (@{$self->{_buttons}}) {
    unless ($i eq $buttonnr) {
      push @WStack, $button;
      push @IStack, $self->{_images}[$i];
    }
    $i++;
  }
  @{$self->{_buttons}}=@WStack;
  @{$self->{_images}}=@IStack;
  return $#{$self->{_buttons}}+1;
}

sub getCode {
  my $self = shift;
  my $code="";
  if($self->{_text}) { $code.=" text \"$self->{_text}\" "}
  if($self->{_orientation}) { $code.=" $self->{_orientation} "}
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  if($self->{_orientation}) { $code.=" { "}
  if ($self->{_title}) { $code.=" text \"$self->{_title}\"; "}
  my $i=1;
  foreach $button (@{$self->{_buttons}}) { 
    $code.="button \"$button\" ";
    if ($self->{_var}) { $code.=" -var $self->{_var} -set \"$i\"" }
    if ($self->{_images}[$i-1]) { $code.=" -image \"$self->{_images}[$i-1]\"" }
    $i++;
    $code.=" -exit;"
  }
  if($self->{_orientation}) { $code.=" }  "}
  if($self->{_btext}) { $code.=" text \"$self->{_btext}\"; "}
 # print "code is:\n$code\n";
  return $code;
}

1; # Keep require happy
