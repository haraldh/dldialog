#!/usr/bin/perl
####################################################
#						   #
# File:		DlFileSelect.pm        	           #
#

package DlFileSelect;
use DlDialog;
####################################################
#
#
# set my port for the dialog to defaults
# Schnittstellen
$fs_to_mount = '/dev/cdrom';      # filesystem to mount
$file_filter = '';                # files to show (regex)
$show_select = '2 3';               # which files to show (1-3)
$sort_select = '1';              # sorting rule
# Signals
$_mount_fs;
$_change_cd;                        # starts a wizzard, to change Disk
$_act_select;                       # refresh lists
# privat
$dir_select = '';                  # number of current entrance in dirlist
$start_dir = '';                   # text of the dirname-inputline
$file_select = '';                 # same for filelist
$file_text = '';                   # text of the filename-inputline
#%month = {Jan=>01,Feb=>02,Mär=>03,Apr=>04,Mai=>05,Jun=>06,Jul=>07,Aug=>08,Sep=>09,Okt=>10,Nov=>11,Dez=>12};

sub new {
  my $base = shift;
  my $class = ref($base) || $base;
  my $self = {};
  my ($package, $file, $line) = caller();
  if ($file =~ /(.*\/)*([^\/]+)/) { $file = $2}
  $self->{file} = $file;
# first building the Widget

  $dialog = new DlDialog("$file : Datei-Auswahl");
  $maingroup = new DlWidgetGroup('row');
  $leftgroup = new DlWidgetGroup('col');
  $rightgroup = new DlWidgetGroup('col');
  $topgroup = new DlWidgetGroup('row');
  $showgroup = new DlWidgetGroup('row');
  $dirgroup  = new DlWidgetGroup('col');
  $dirlistgroup  = new DlWidgetGroup('row');
  $confgroup = new DlWidgetGroup('row');
  $mountgroup = new DlWidgetGroup('row');
  $spacer = new DlWidgetGroup('row','',100,100);

  #leftgroup
  $dirline = new DlInputField('Verzeichniss','top','start_dir','true');
#  $actbutton = new DlButton('aktualisieren','_act_select');
#  $topgroup->insertElement($actbutton,$dirline),

  $dirlist = new DlList('Verzeichnisse','dir_select','','true');
  $dirlistgroup->insertElement($dirlist);
  $dirlistgroup->setImage('top.gif','b');
  $filterline = new DlInputField('Filter','t','file_filter');
  $dirgroup->insertElement($filterline,$dirlistgroup);
  $filelist = new DlList('Dateien','file_select','','true',100,100);
  $showgroup->insertElement($dirgroup,$filelist);

  $fileselectline = new DlInputField('Dateiname','t','file_text');

  $leftgroup->insertElement($dirline,$showgroup,$fileselectline);

  #rightgroup
  $selectlist = new DlCheckList('anzeigen','show_select');
  $sortlist = new DlRadioList('sortiert nach','sort_select');
  $confgroup->insertElement($selectlist,$sortlist);

  $fscombo = new DlComboBox('Nicht montierte Dateisysteme','fs_to_mount');
  $mountbutton = new DlButton('montieren','_mount_fs');
  $mountgroup->insertElement($mountbutton);
  $mountgroup->setImage('mount.xpm');
  $rightgroup->insertElement($selectlist,$sortlist,$fscombo,$mountgroup);

  $maingroup->insertElement($leftgroup,$rightgroup);

  $dialog->addGroup($maingroup);

  $show_hidden = $selectlist->insertButton('Versteckte Dateien');
  $show_backup = $selectlist->insertButton('Backups (~)');
  $show_empty = $selectlist->insertButton('leere Dateien');

  $sort_date = $sortlist->insertButton('Name');
  $sort_date = $sortlist->insertButton('Datum');
  $sort_size = $sortlist->insertButton('Größe');

    # und Referenz zurückgeben
    bless($self, $class);
    return $self;
}


sub get_dirlist {
  my $dir = shift || "/";
  my $select = shift || $show_select;
  my @dirs;
  my $dircommand = "ls -l";
  if ($select =~ /$show_hidden/) {
    $dircommand .= "a"}
  my @list = `$dircommand $dir | grep "^d"`;
  foreach (@list) {
    /\s+(\S+)$/;
    push @dirs, $1;
  }
  unless ($dirs[1] =~ /\.\./) { unshift @dirs,".",".."}
  print "Dir hat : @dirs\n";
  return @dirs;
  undef $dir_select;
}

sub get_filelist {
  my $self = shift;
  %{$self->{file}}=();
  my $d = `date`;
  $d =~ /\s(\d+)$/;
  my $year = $1;
  my $dir = shift || "/";
  my $filter = shift || $file_filter;
  my $select = shift || $show_select;
  my $sort = shift || $sort_select;
#  my %file;
  my @files;
  my $dircommand = "ls -l";
  if ($select =~ /$show_hidden/) {
    $dircommand .= "a"}
  my @list = `$dircommand $dir | grep -v "^d"`;
  foreach (@list) {
#    print;
    /(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(.+)/;
    # filter all
#    next unless $9 =~ /$filter/;
    # store informations
    ($filename,$temp,$dest) = split ' ', $9;
    $self->{file}{$filename}{dest} = $dest;
    $self->{file}{$filename}{perms}=$1;
    $self->{file}{$filename}{owner}=$3;
    $self->{file}{$filename}{group}=$4;
    $self->{file}{$filename}{size}=$5;
    $self->{file}{$filename}{month}=$6;
    $self->{file}{$filename}{day}=$7;
    $time = $8;
    $self->{file}{$filename}{year} = $time;
    if ($time =~ /:/) {
      $self->{file}{$filename}{year} = $year;
      $self->{file}{$filename}{time} = $time;
    }
  }
  # build an array
  my $size;
  foreach $file (sort keys %{$self->{file}}) {
    if ($file) {
      $size += $self->{file}{$file}{size};
      if ($self->{file}{$file}{perms} =~ /^l/) {
	$filemark = "\$";
      } else {$filemark = "!"}
#    $line = "$self->{file}{$file}{day}.$self->{file}{$file}{month}.$self->{file}{$file}{year} * $self->{file}{$file}{size} $filemark $file";
#      $line = "$file";
      push @files, $file }
  }
  unshift @files, $size;
  return @files;
}

sub get_unmounted_dev {
  my %devices;
  my @fstab = `cat /tmp/fstab 2>/dev/null`;
  # get fstab entries
  foreach $dev (@fstab) {
    next if $dev =~ m/^#[^\/]/;
    if ($dev =~ m/^\/proc /) {$proc='true';next;}
    ($device, $mountp) = split " ", $dev;
    chomp $device;
    chomp $mountp;
    if ($device) {
      unless ($mountp eq 'swap') { $devices{$device}=$mountp}
    }
  }
  # delete mounted systems
  my @mounted = `mount`;
  foreach $mount (@mounted) {
    ($fs) = split " ", $mount;
    chomp $fs;
    delete $devices{$fs}
  }
  return %devices;
}  

# fill the Widget with live

sub build {
  my $self = shift;
#  print "self->{basedir} is ".$self->{basedir}."\n";
  $start_dir = shift || $self->{basedir};
#  print "startdir set to $start_dir\n";
  $fs_to_mount = shift || $fs_to_mount;
  $file_filter = shift || $file_filter;
  my $sel = shift;
  if ($sel) {
    $show_select = "1 " if $sel=~/h/;
    $show_select .= "2 " if $sel=~/b/;
    $show_select .= "3 " if $sel=~/e/;
  }
  my $sort = shift;
  if ($sort) {
    $sort_select = "1" if $sort=~/n/;
    $sort_select = "2" if $sort=~/d/;
    $sort_select = "3" if $sort=~/s/;
  }
  # get the directories
  $self->{basedir} = $start_dir;
  my @dirs = get_dirlist($start_dir,$show_select);
  $dir_text = $start_dir;
  $dirlist->clear();
  $anz = @dirs;
  $dirlist->setTitle("$start_dir: $anz Verzeichnisse");
  $dirlist->insertItem(@dirs);
  # now get the files
  my ($size, @files) = get_filelist($self,$start_dir,$file_filter,$show_select,$sort_select);
  $filelist->clear();
  $filelist->insertItem('');
  foreach $file (@files) {
    if ($self->{file}{$file}{perms} =~ /^l/) {
      $filelist->setColor($filelist->insertItem($file),'green')
    }
    elsif ($self->{file}{$file}{perms} =~ /x/) {
      $filelist->setColor($filelist->insertItem($file),'red')
    }
    else {
      $filelist->setColor($filelist->insertItem($file),'blue')
    }
  }

    
#  $filelist->insertItem(@files);
  $anz = @files;
  $filelist->setTitle("$anz Dateien: $size Bytes");
  # now fill some widgets
  $fscombo->clearItems;
  my %devices = get_unmounted_dev;
  foreach $dev (sort keys %devices) {
    $dev = $dev." an ".$devices{$dev}."\n";
    $fscombo->insertItem($dev);
  }
  
}

sub get_it {
  my $self = shift;
  my $mode = shift;
  unshift @_,$self;
  build(@_);
################Main-loop
  for (;;) {
    $status = $dialog->show;
#    print "status is $status:\ndir_select is $dir_select\n";
#    print "show_select is $show_select: sort_select is $sort_select\nfile_filter is $file_filter:\nmount_fs is $_mount_fs\n";
    $file_text = $filelist->getItem($file_select);
    if ($status eq 'ok') {                        # ok
      if ($mode eq 'dir') { return $self->{basedir} }
      elsif ($mode eq 'file') { return $self->{basedir}.$file_text }
    }
    elsif ($status eq 'back') { return undef }    # cancel
    $cur_dir = $dirlist->getItem($dir_select);
    if ($cur_dir eq '.') { $cur_dir = $start_dir."/" }
    elsif ($cur_dir eq '..') { 
      $start_dir =~ s/((\/[^\/]+)*)\/[^\/]+/\1/;
      $cur_dir = $start_dir."/";
      $file_text = '';
    }
    else {
      $cur_dir = $start_dir."/".$cur_dir;
      $file_text = ''; 
   }
    $cur_dir =~ s/\/\//\//;                     # eleminate doubleslashes
    $self->{basedir} = $cur_dir;
    # next loop
    if ($_mount_fs) {
      my $fs = $fscombo->getItem($fs_to_mount);
      $fs =~ /^(\S+).*/;
      system("mount", $1);
    }
    $dir_select='';
    $file_select='';
    $_mount_fs='';
#    print "self->{basedir} is ".$self->{basedir}."\n";
    build($self);
  }
}

sub getdir {
  my $self = shift;
  unshift @_,'dir';
  unshift @_,$self;
  get_it(@_);
}

sub getfile {
  my $self = shift;
  unshift @_,'file';
  unshift @_,$self;
  get_it(@_);
}


1;
  
