#!/usr/bin/perl
#
# Modul I18n


package I18n;
use Cwd;

sub new {
  my $thisdir = cwd();
  my $base = shift;
  my $class = ref($base) || $base;
  my $self = {};
  my ($package, $file, $line) = caller();
  $file =~ s/^.\//$thisdir\//;
  $file =~ s/^~\//$ENV{HOME}\//;
#  print "Caller gibt zurück:$package\n$file\n$line\n:\n";
  # Uebergebene oder ermittelte Attribute merken
  my $tfile = shift || $file;
  my $lang = shift || $ENV{LANG} || 'de'; # only for debugging purpose
  $tfile = "$tfile.$lang";
#    print "tfile ist $tfile\n";
  if (-r "$tfile") {$self->{_translation_file} = $tfile}
  open TRANS, "<$self->{_translation_file}" or warn "Cannot open translationfile $self->{_translation_file}\n";
  while (<TRANS>) {
    chomp;
    next if /^#/;
      if ((/^\s*$/) && $msgid) {
        $ismsgstr = '';
        chomp $msgstr;
        chomp $msgid;
        $self->{text}{$msgid} = $msgstr || $msgid;
        $msgstr = '';
        $msgid = '';
        next;
      }
      next if /^\s*$/; 
      if (($msgid) && (/^msgstr\s+("[^"]*")/)) { 
        $ismsgid = '';
        $ismsgstr = 'true';
        $msgstr = $1;
        $msgstr =~ s/^"//;
        $msgstr =~ s/"$//;
        next
      }
      if (/^msgid\s+("[^"]*")/) {
        $ismsgid = 'true';
        $msgid = $1;
        $msgid =~ s/^"//;
        $msgid =~ s/"$//;
        next
      }
      if ($ismsgid) {
        s/^"//;
        s/"$//;
        $msgid .= "\n".$_;
        next
      }      
      if ($ismsgstr) {
        s/^"//;
        s/"$//;        
        $msgstr .= "\n".$_;
        next
      }
      else {
        print "Undefinierte Zeile gefunden:";
        print;
      }
    }
    close TRANS;
    $self->{_caller_package} = $package;
    bless($self, $class);
    return $self;
}


sub t {
  my $self = shift;
  $text = shift;
  my $newline = chomp $text;
#  print "Text ist :$text:\n";
  $trans = $self->{text}{$text} || $text ;
  if ($newline) { $trans .= "\n"} 
  return $trans;
} 


sub all {
  my $self = shift;
  foreach $text (sort keys %{$self->{text}}) {
    print "Original:$text:\n";
    print "Übersetzung:$self->{text}{$text}:\n";
  }
}

1;
