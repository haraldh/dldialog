#!/usr/bin/perl
####################################################
#						   #
# File:		DlWidgetGroup.pm  	           #
#

package DlWidgetGroup;

####################################################
#
# Konstruktor new: legt ein neues  DlWidgetGroup-Objekt an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Orientierung ( r|row|c|col|f|form): default 'col'
# Titel: Titel der WidgetGruppe
# Höhe, Breite: Geometrie der Box (tut in dldialog noch net)




sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my ($orient, $title, $height, $width) = @_;
    if ($orient) {
        if ($orient =~ /(row|r)/i) { $self->{_orienation} = "row" }
        elsif ($orient =~ /(col|c)/i) { $self->{_orienation} = "col" }
        elsif ($orient =~ /(form|f)/i) { $self->{_orienation} = "form" }
	else { $self->{_orienation} = "col" }
	      }
#    my $title = shift;
    if ($title) { $self->{_title} = $title;}
    if ($height) { $self->{_height} =$height}
    if ($width) { $self->{_width} =$width}
 
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

sub setImage {
  my ($self, $image, $pos) = @_;
  if ($pos=~/^b/i) {$self->{_bimage}=$image}
  else {$self->{_image}=$image}
}
  

sub insertElement {
  my $self = shift;
  my @elements =  @_;
  push @{$self->{_elements}} ,@elements;
  my ($element,$elem);
  foreach $element (@elements) {
    if ($element->{_var}) {
      push @{$self->{_vars}}, $element->{_var}
    }
    if (@{$element->{_vars}}) {
      push @{$self->{_vars}}, @{$element->{_vars}}
    }
  }
  return $#{$self->{_elements}};
}
  

sub getCode {
  my $self = shift;
  my $element;
  my $code="text \"$self->{_title}\"; $self->{_orienation} ";
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  $code.=" { ";
  if($self->{_text}) { $code.=" text \"$self->{_text}\"; "}
  if($self->{_image}) { $code.=" image \"$self->{_image}\"; "}
  foreach $element (@{$self->{_elements}}) {
    $code .= $element->getCode();
  }
  if($self->{_bimage}) { $code.=" image \"$self->{_bimage}\"; "}
  if($self->{_btext}) { $code.=" text \"$self->{_btext}\"; "}
  $code .=" }";
  return $code;
}


1; # Keep require happy
