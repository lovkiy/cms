<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Форма редактирования пункта меню...</h3></header>

<form action="<?=BASEURL.LANG?>admin/editmenupage/<?=$menu_id?>/<?=$page_id?>" method="POST">
    <input type="text" name="pagename" value="<?=$page?>" />
    
<footer>
        <input class="alt_btn" type="submit" value="Изменить" />
    </footer>
</form>

</article><!-- end of content manager article -->
