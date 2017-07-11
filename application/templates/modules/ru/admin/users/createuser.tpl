<?php  if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Создание пользователя...</h3></header>

<h3><?=@$message?></h3>
<form action="<?=BASEURL.LANG?>admin/createuser" method="POST">
    <p><b><i>Логин:</i></b></p> 
    <input type="text" name="user_login" value="" /><br />
    <p><b><i>Имя пользователя:</i></b></p> 
    <input type="text" name="user_name" value="" /><br />
    <p><b><i>Пароль:</i></b></p> 
    <input type="password" name="user_password" value="" /><br />
    <p><b><i>Подтверждение пароля:</i></b></p> 
    <input type="password" name="user_password_confirm" value="" /><br />
    <p><b><i>Шабон пользователя:</i></b></p> 
    <select name="user_tpl_id">
    <? for($x=0;$x<sizeof($userstpl);$x++): ?>
        <option value="<?=$userstpl[$x]['id']?>"><?=$userstpl[$x]['name']?></option>
    <? endfor; ?>
    </select>
    
<footer>
        <input class="alt_btn" type="submit" value="Создать" />
    </footer>
</form>

</article><!-- end of content manager article -->