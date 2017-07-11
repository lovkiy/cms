<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/


if($sel_params):
    foreach($sel_params as $key=>$val):
     $url.="/".$val; 
    endforeach;
else:
    $url = "";
endif;

?>
язык сайта&nbsp;&nbsp;

<? for($x=0;$x<sizeof($langs);$x++):?>
    <? if(LANGDIR==$langs[$x]['code']):?>
        <img align="middle" src="<?=BASEURL?>images/lang_<?=$langs[$x]['code']?>.gif" alt="" />        
    <? else: ?>   
      <? $code = (LANGUEGE == $langs[$x]['code'] )? "" : $langs[$x]['code']."/"; ?>
        <a href="<?=BASEURL.$code.$selected_page.$url?>">
            <img align="middle" src="<?=BASEURL?>images/lang_<?=$langs[$x]['code']?>.gif" alt="" />
        </a> 
    <? endif;?>
<? endfor; ?>