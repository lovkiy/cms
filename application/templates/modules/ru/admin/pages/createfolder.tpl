<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Форма создания папки</h3></header>
<form action="<?=BASEURL.LANG?>admin/addfolder" method="POST">
    <p>
        <b><i>Введите название папки:</i></b>
        <input type="text" name="name" style="width: 80%;" />
    </p>    
    <footer style="text-align: center;">
        <input style="margin: 5px 0 0 0;" class="alt_btn" type="submit" value="Создать папку" />
    </footer>
</form>

</article><!-- end of content manager article -->