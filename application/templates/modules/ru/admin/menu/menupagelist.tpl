<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
//print_r($menupagelist);
?>

<article class="module width_full">
    <header><h3 class="tabs_involved">Список страниц меню</h3></header>

<a href="<?=BASEURL.LANG?>admin/movemenu/<?=$menu_id?>/<?=$id_moved?>/0"><b>Корень</b></a><br />
<? for($x=0;$x<sizeof($menupagelist);$x++): ?>
    <?=$menupagelist[$x]['id']?> 
    <a href="<?=BASEURL.LANG?>admin/movemenu/<?=$menu_id?>/<?=$id_moved?>/<?=$menupagelist[$x]['id']?>">
        <?=$menupagelist[$x]['name']?>
    </a><br />
<? endfor; ?>

<footer> </footer>


</article><!-- end of content manager article -->