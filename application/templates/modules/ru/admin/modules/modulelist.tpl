<?php  if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<?=$message?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Список модулей...</h3>
    </header>

<table class="tablesorter" cellspacing="0"> 
        <thead> 
            <tr> 
                <th>№</th>
    		<th>Название</th> 
    		<th>Описание</th> 
    		<th>Настройки</th> 
    		<th>Действие</th> 
            </tr> 
	</thead> 
	<tbody> 
            <? for($x=0;$x<sizeof($modulelist);$x++): ?>
            <tr> 
                <td><?=$modulelist[$x]['id']?></td>
    		<td><?=$modulelist[$x]['name']?></td> 
    		<td><?=$modulelist[$x]['description']?></td> 
    		<td>
                <? if($modulelist[$x]['available']==1): ?>
                    <a href="<?=BASEURL.LANG?>admin/settings/<?=$modulelist[$x]['id']?>">
                        <input type="image"title="Настройки" src="<?=BASEURL?>images/admin/icn_edit.png">
                    </a>
                <? endif; ?>    
                </td> 
    		<td>
                <? if($modulelist[$x]['available']!=1): ?>
                    <a onclick="if (confirm('Вы действительно хотите установить данный модуль ?') ) {
                                                location.href='<?=BASEURL.LANG?>admin/modules/<?=$modulelist[$x][id]?>/install';
                                             } else { return };">                    
                        <input type="image" title="Установка" src="<?=BASEURL?>images/admin/install_icon.jpg">
                    </a>
                <? else: ?>
                    <a onclick="if (confirm('Вы действительно хотите удалить данный модуль ?') ) {
                                                location.href='<?=BASEURL.LANG?>admin/modules/<?=$modulelist[$x][id]?>/uninstall';
                                             } else { return };">                    
                        <input type="image" title="Удаление" src="<?=BASEURL?>images/admin/icn_trash.png">
                    </a>
                <? endif; ?>                    
                </td> 
            </tr> 
            <? endfor; ?>
	</tbody> 
    </table>		

<footer></footer>

</article><!-- end of content manager article -->