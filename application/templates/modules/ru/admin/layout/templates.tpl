<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Список доступных шаблонов ...</h3></header>
<form action="<?=BASEURL.LANG?>admin/ceratelayout" method="POST">
    <h4>Введите название макета: <input type="text" name="layout_name" /></h4>
    <? foreach($templatelist as $template): ?>
        <b><input type="checkbox" name="layout" value="<?=$template?>" /><?=$template?></b><br />
    <? endforeach; ?>

<footer>
    <input class="alt_btn" type="submit" value="Создать" />
</footer>
</form>
</article><!-- end of content manager article -->