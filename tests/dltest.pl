#!/usr/bin/perl -w
# 
#
require "tdialog.pm";
require "DlWidgetGroup.pm";
require "DlRadioList.pm";
require "DlCheckList.pm";
require "DlList.pm";
require "DlComboBox.pm";
require "DlButtonGroup.pm";
require "DlInputField.pm";


$inputField = new DlInputField("Eingabe","t","input","i");
$aRadioList = new DlRadioList("some Radiobuttons","radio");
$bRadioList = new DlRadioList("other Radiobuttons","radiob=2");
$aCheckList = new DlCheckList("a Checklist","checked=1 3");
$aButtonGroup = new DlButtonGroup("col","some Buttons","top","button");
$right=$aButtonGroup->insertButton("-->");
$left=$aButtonGroup->insertButton("<--");
$okay = $aButtonGroup->insertButton("Ok");
$aList = new DlList("a List","alist");
$bList = new DlList("a List","blist");
$aBox = new DlComboBox("a Box","box=4");
$myWidget = new DlWidgetGroup("row","WidgetTest");
$anotherWidget =  new DlWidgetGroup("row","AnotherWidgetTest",100,50);
$anotherWidget->insertElement($inputField);
$aThirdWidget =  new DlWidgetGroup("row","AThirdWidgetTest");
#$aThirdWidget->insertElement($aCheckList);
$aThirdWidget->insertElement($aList);
$aThirdWidget->insertElement($aButtonGroup);
$aThirdWidget->insertElement($bList);
# $aThirdWidget->insertElement($aBox);
$myWidget->insertElement($aRadioList);
$myWidget->insertElement($bRadioList);
$mydialog = new tdialog("Test");
$mydialog->addGroup($myWidget);
$i = $mydialog->addGroup($anotherWidget);
$mydialog->addGroup($aThirdWidget);
my $oldtitle=$myWidget->setTitle("Geändert");
$e = $mydialog;
$default=$aRadioList->insertButton("Eins");
$aRadioList->insertButton("Zwei","Fünf","sechs");
$radio=$default;
@test=("Zwei","Fünf","sechs");
$bRadioList->insertButton("Eins");
$bRadioList->insertButton(@test);
$bRadioList->insertButton("Drei");
$bRadioList->insertButton("gaaanz viele");
$aCheckList->insertButton("Eins");
$aCheckList->insertButton("Zwei");
$aCheckList->insertButton("Drei");
$aCheckList->insertButton("Vier");
@shells=`cat /etc/shells`;
$aList->insertItem(@shells);
$aBox->insertItem(@shells);
$aBox->setText("Shellauswahl","behind");
$mydialog->setVars("radio","radiob","checked","list","button", "input");
print "Ok ist $okay, left ist $left, right ist $right\n";
$input = "128.32.1.1";
for (;;) {
  $alist=0;
  $blist=0;
  $e->show();
  if ($button eq $right) { $bList->insertItem($aList->removeItem($alist)) }
  elsif ($button eq $left) { $aList->insertItem($bList->removeItem($blist)) }
  else {last}
}
$A=$aList->getList();
print "Liste A ist jetzt:\n @$A\nListe B ist jetzt:\n @{$bList->getList()}\n";
#$ret = $e->removeGroup($i);
#print "Verbleiben: $ret\n";
#$e->setTitle("Geschrumpft");
#$bRadioList->removeButton($radiob);
#$myWidget->setTitle($oldtitle);
#$e->show();
print "Resultat: $radio, $radiob, Checkbox: $checked, Liste: $alist & $blist, Box: $box Button: $button und eingegenen wurde: $input\n";
