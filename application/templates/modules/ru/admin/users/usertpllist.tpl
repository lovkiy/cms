<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Список шаблонов пользователей</h3></header>

<? for($x=0;$x<sizeof($tpls);$x++): ?>
ID: <?=$tpls[$x]['id']?> Name: <?=$tpls[$x]['name']?> <a>Редактировать</a> <a>Удалить</a><br /> 
<? endfor; ?>
<footer></footer>
</article><!-- end of content manager article -->