#!/usr/bin/perl
####################################################
#						   #
# File:		DlInputField.pm                    #
#

package DlInputField;

####################################################
#
# Konstruktor new: legt ein neues  DlInputField-Objekt an und gibt
# die Referenz darauf zurück.
# Übergabeparameter (optional, aber in fester Reihenfolge):
# Titel: Titel des InputFields
# Pos (t[op]|b[ottom]|l[eft]|r[ight]): Position des Titels (default links)
# Var: Name der Variablen, die die Eingabe zurückgibt. 
# Typ (n[umeric]|p[asswd]|i[p-like]|pn|pi): Typ des Eingabewertes 
# Höhe, Breite: Geometrie der Box (tut in dldialog noch net)


sub new {
    my $base = shift;
    my $class = ref($base) || $base;
    my $self = {};
    my ($package, $file, $line) = caller();

    # Uebergebene Attribute merken
    my ( $title, $titlepos, $var, $exit, $typ, $height, $width) = @_;
    if ($title) { $self->{_title} = $title;}
    if ($titlepos) {
      if ($titlepos=~/^t/i) { $self->{_pos} = "before";  $self->{_orient}="col"}
      elsif ($titlepos=~/^b/i) { $self->{_pos} = "behind";  $self->{_orient}="col"}
      elsif ($titlepos=~/^l/i) { $self->{_pos} = "before";  $self->{_orient}="row"} 
      elsif ($titlepos=~/^r/i) { $self->{_pos} = "behind";  $self->{_orient}="row"}
      else { $self->{_pos} = "before";  $self->{_orient}="row"} 
    }
    if ($exit) { $self->{_exit} = 'true'}
    if ($var) {
      if ($var=~/=/) {      # '=' im Variablennamen führt zu ParseError
	($var, $value) = split /=/ , $var;    # trennen
	if ($value) { $self->{_value} =$value}  #und Wert merken
      }
      $self->{_var} = $var;}
    if ($typ) {
      if ($typ=~/^p/i) {
	if ($typ=~/\sn/i) { $self->{_typ}="-passwd -numeric"}
	elsif ($typ=~/\si/i) { $self->{_typ}="-passwd -ip"}
	else { $self->{_typ}="-passwd"}
      }
      elsif ($typ=~/^n/i) { $self->{_typ}="-numeric"}
      elsif ($typ=~/^i/i) { $self->{_typ}="-ip"}
    }
    if ($height) { $self->{_height} =$height}
    if ($width) { $self->{_width} =$width}

    bless($self, $class);
    return $self;
}

sub getCode {
  my $self = shift;
  my $code=" $self->{_orient} ";
  if ($self->{_height}) { $code.=" -height $self->{_height} " }
  if ($self->{_width}) { $code.=" -width $self->{_width} " }
  $code .= " { ";
  if ($self->{_title} && ($self->{_pos} eq "before")) { $code.=" text \"$self->{_title}\"; "}
  if ($self->{_value}) { $code .=" $self->{_var}=\"$self->{_value}\"; "}
  $code .= " input ";  
  if ($self->{_var}) { $code.=" -var $self->{_var} " }
  if ($self->{_typ}) { $code.=" $self->{_typ} "}
  if ($self->{_exit}) {$code .= "-exit "}  
  $code .= " ; ";
  if ($self->{_title} && ($self->{_pos} eq "behind")) { $code.=" text \"$self->{_title}\"; "}
  $code .= " } ";
  
  return $code;
}










1; # Keep require happy
