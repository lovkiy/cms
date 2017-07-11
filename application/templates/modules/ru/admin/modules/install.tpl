<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
?>

<article class="module width_full">
    <header><h3 class="tabs_involved">Установка модуля <span style="color:blueviolet;"><?=$install['name']?></span></h3></header>
     <?=$install['info']?><br />
     <? if(!empty($install['info'])): ?>
        <input type="button" value="Установить" onclick="location.href='<?=BASEURL.LANG?>admin/install/<?=$module_id?>/true'" /> 
     <? else: ?>
        <input type="button" value="Выход" onclick="location.href='<?=BASEURL.LANG?>admin/modules'" />
     <? endif; ?>   
    <footer></footer>
</article><!-- end of content manager article -->  