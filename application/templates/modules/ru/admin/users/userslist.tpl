<?php  if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
//print_r($userslist);
?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Список пользователей&nbsp;|&nbsp;
            <a href="<?=BASEURL.LANG?>admin/createuser">Добавить</a>&nbsp;|&nbsp;
            <a href="<?=BASEURL.LANG?>admin/usertpllist">Просмотр шаблонов</a>&nbsp;|&nbsp;
            <a href="<?=BASEURL.LANG?>admin/createusertpl">Создание шаблона</a>
        </h3>
    </header>

<? for($x=0;$x<sizeof($userslist);$x++): ?>
    <?=$userslist[$x]['id']?> <?=$userslist[$x]['user_name']?> <a href="<?=BASEURL.LANG?>admin/edituser/<?=$userslist[$x]['id']?>">Редактировать</a> <a href="">Удалить</a> <br />
<? endfor; ?>
 <footer></footer>
 </article><!-- end of content manager article -->