<?php  if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Редактирование данных пользователя...</h3></header>

<h3><?=@$message?></h3>
<form action="<?=BASEURL.LANG?>admin/edituser/<?=$id?>" method="POST">
    Логин: <input type="text" name="user_login" value="<?=$user_login?>" /><br />
    Имя пользователя: <input type="text" name="user_name" value="<?=$user_name?>" /><br />
    Введите новый пароль: <input type="password" name="user_password" value="" /><br />      
   
<footer>
        <input class="alt_btn" type="submit" value="Изменить" />
    </footer>
</form>

</article><!-- end of content manager article -->
