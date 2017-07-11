<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>

<article class="module width_full">
    <header><h3 class="tabs_involved">Создание виджета...</h3></header>


<form action="<?=BASEURL.LANG?>admin/<?=$action?>" method="POST">
    Введите название виджета:   <input type="text" name="widgetname" /><br />
 <p>Контент</p>
 <textarea name="content" style="width: 95%"></textarea>
    
<footer>
        <input class="alt_btn" type="submit" value="Создать" />
    </footer>
</form>

</article><!-- end of content manager article -->    

