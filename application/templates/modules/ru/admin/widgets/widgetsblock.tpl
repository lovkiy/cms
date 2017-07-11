<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<h3>Прикрепление виджета к странице</h3>

<table>
    <th>ID</th>
    <th>Название виджета</th>
    <th>Вкл./Выкл.</th>
    <th>Язык</th>
    
        <? for($x=0;$x<sizeof($block['widgets']);$x++): ?> 
        <tr>
            <td><?=$block['widgets'][$x]['id']?></td>
            <td><?=$block['widgets'][$x]['name']?></td>
            <? if(in_array($block['widgets'][$x]['id'], $block['widget_id'])): ?>
                <td>
                    <a href="<?=BASEURL.LANG?>admin/editpageview/widgets/<?=$param['params'][2]?>/<?=$param['params'][3]?>/off/<?=$block['widgets'][$x]['id']?>">
                        <img src="<?=BASEURL?>images/admin/ico_on.gif" />
                    </a>
                </td>
            <? else: ?>
                <td>
                    <a href="<?=BASEURL.LANG?>admin/editpageview/widgets/<?=$param['params'][2]?>/<?=$param['params'][3]?>/on/<?=$block['widgets'][$x]['id']?>">
                        <img src="<?=BASEURL?>images/admin/ico_off.gif" />
                    </a>
                </td>
            <? endif; ?>
            <td>
                <select name="lang_id" onchange="location.href='<?=BASEURL.LANG?>admin/editpageview/widgets/<?=$param[params][2]?>/<?=$param[params][3]?>/lang/<?=$block[widgets][$x][id]?>/'+options[selectedIndex].value;">
                    <option value="0">--</option>
                <? for($y=0;$y<sizeof($lang);$y++): ?>
                    <? if($lang[$y]['id'] == $block['lang_id'][$block['widgets'][$x]['id']]): ?>
                        <option value="<?=$lang[$y]['id']?>" selected="selected" ><?=$lang[$y]['code']?></option>
                    <? else: ?>
                        <option value="<?=$lang[$y]['id']?>"><?=$lang[$y]['code']?></option>
                    <? endif; ?>
                <? endfor; ?>    
                </select>
            </td>
        </tr>
        <? endfor; ?>
    
</table>
