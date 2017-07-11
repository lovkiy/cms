<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Управление Текстовыми блоками</h3>        
    </header>
<h3>Язык:
    <select name="lang_id" onchange="location.href='<?=BASEURL.LANG?>admin/editpageview/<?=$param[params][1]?>/<?=$param[params][2]?>/<?=$param[params][3]?>/'+this.value">        
    <? for($x=0;$x<sizeof($block);$x++): ?>
        <option value="<?=$block['lang'][$x]['id']?>"><?=$block['lang'][$x]['langname']?></option>
    <? endfor; ?>
    </select>
</h3>
<form action="<?=BASEURL.LANG?>admin/editpageview/<?=$param['params'][1]?>/<?=$param['params'][2]?>/<?=$param['params'][3]?>/<?=$param['params'][4]?>" method="POST">
    <textarea id="elm1" name="description" rows="35" cols="80" style="width: 80%"><?=$block['description']?></textarea><br />
    <input type="submit" value="Изменить" />
</form>
<footer></footer>

</article><!-- end of content manager article --> 