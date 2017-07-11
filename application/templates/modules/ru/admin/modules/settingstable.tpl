<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
* Description of settingstable
*
* @author Alex
*/
?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Настройки модуля</h3>
    </header> 
    <form action="<?=BASEURL.LANG?>admin/settings/<?=$module_id?>" method="POST">
        <table style="width: 80%">
            <tr>
                <th align="left">№</th>
                <th align="left">Описание</th>
                <th align="left">Значение</th>
            </tr>
            <? for($x=0;$x<sizeof($settings);$x++): ?>
            <tr>
                <td><?=$settings[$x]['id']?></td>
                <td><?=$settings[$x]['description']?></td>
                <td>
                    <input type="text" name="<?=$settings[$x]['id']?>" value="<?=$settings[$x]['value']?>" />  
                </td>
            </tr>
            <? endfor; ?>
        </table>

        <footer>
            <input type="submit" value="Изменить" />
        </footer>
    </form>
</article><!-- end of content manager article -->
