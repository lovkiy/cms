<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Редактирование виджета</h3></header>
    <form action="<?=BASEURL.LANG?>admin/editwidget/<?=$id?>" method="POST">
        Введите название виджета:   <input type="text" name="name" value="<?=$name?>"/><br />
        <p>Контент</p>
        <textarea name="content" style="width: 95%"><?=$content?></textarea>

    <footer>
            <input class="alt_btn" type="submit" value="Изменить" />
    </footer>
</form>

</article><!-- end of content manager article -->  
