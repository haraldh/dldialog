#!/usr/bin/perl -I/home/tom
use Getopt::Long;
use I18n;

$i = new I18n;
my $date = `date`;

sub print_usage {
  print $i->t("maketransfile Usage:\nmaketransfile [-t|template progfilename] | [-f|file filetotranslate] \nfor more informations try: maketransfile -h|help\n");
exit;
}

sub print_help {
  print $i->t("Help\n");
  $i->all();
exit;
}

sub print_no_i18n {
  my $filetotranslate = shift;
#print $i->t("\$filetotranslate does not provide internationalisation\n");
  print "$filetotranslate".$i->t(" does not provide internationalisation\n");
}

sub make_translation {
  my $filetotranslate = shift;
  my $lang = shift || $ENV{LANG} || 'de';
  my $templatefile = $filetotranslate."tpl";
  my $destinationfile = $filetotranslate.$lang;
  
exit;
}

sub make_template {
my $filetotranslate = shift;
my $template = "$filetotranslate.tpl";
open PROG, "<$filetotranslate" or die $i->("\aCannot open $filetotranslate");
$line_nr = 0;
while (<PROG>) {
  chomp;
  $line_nr++;
  next if /^#/ || /^\s*$/;
  if (/\$([\w]+)\s*=\s*new\s+I18n(\(['"][\w\d\.]*["']\))*/) { 
    $i18nvar = $1;
    print "found I18n-Var = $i18nvar\n";
    $temp = $2;
    if ($temp =~ /\(['"]([\w\d\.]*)["']\)/) { $temp = $1 }
    else { $temp = "" }
    if ($temp) { $template = "$temp.tpl" }
    print "and template is $template\n";
    open TEMPLATE, ">$template";
    print TEMPLATE "# This is a template file for internationalisation\n# of the program $filetotranslate,\n# automatically generated at $date# by maketransfile.pl (C) by Thomas Hagedorn tom\@delix.de\n\n";
    next;
    }
  next unless $i18nvar;
  if (/\$$i18nvar->t\((["'])([^\1]*?)\1\)/) { #"
    $msgid = $2;
    $msgid =~ s/\\n$//;
    next if $msg{$msgid};
    $msg{$msgid} = 'true';
    @msgid = split /\\n/, $msgid;
    print TEMPLATE "# $filetotranslate in line nr: $line_nr\n";
    print TEMPLATE "msgid ";
    my $i=0;
      foreach $msgline (@msgid) {
        print TEMPLATE "\"$msgline\"\n";
        $i++;
      }
    print TEMPLATE "msgstr ";
    for ($j=0;$j<$i;$j++) { print TEMPLATE "\"\"\n"}
    print TEMPLATE "\n";
    }
  }
close PROG;
close TEMPLATE;
print_no_i18n($filetotranslate) unless $i18nvar;

exit;
}

print_usage() unless @ARGV;
%option = {};
GetOptions(\%option, "template=s", "file=s", "language=s", "help");
print_help() if $option{help};
make_translation( $option{file}, $option{language} ) if $option{file};
print_usage() if @ARGV;
make_template( $option{template} ) if $option{template};
print "This should not be!\n";

