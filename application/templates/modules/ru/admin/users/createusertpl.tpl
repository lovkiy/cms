<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
//echo "<pre>";
//print_r($views);
//echo "</pre>";
?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Создание шаблона пользователя...</h3></header>

<?=@$message?>
<h3>Отметье те пункты которые будут разрешены пользователю</h3>
<form action="<?=BASEURL.LANG?>admin/createusertpl" method="POST">
    Название шаблона пользователя: <input type="text" name="usertplname" value="" />
    
<table>
    <th></th>
    <th>Название модуля</th>    
<? for($x=0;$x<sizeof($views);$x++):   ?>
    <tr>
        <td>
            <input type="checkbox" name="ability[<?=$views[$x]['id']?>]"  value="<?=$views[$x]['id']?>"/>
            <input type="hidden" name="hide[<?=$views[$x]['id']?>]" value="<?=$views[$x]['id']?>" />
        </td>
        <td><?=$views[$x]['name']?></td>        
    </tr>
<? endfor; ?>
</table><br />
    
<footer>
        <input class="alt_btn" type="submit" value="Создать" />
    </footer>
</form>

</article><!-- end of content manager article -->