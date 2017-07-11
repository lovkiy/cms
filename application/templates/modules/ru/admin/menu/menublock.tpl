<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<h3>Прикрепление меню к странице</h3>

<table>
    <th>ID</th>
    <th>Название виджета</th>
    <th>Вкл./Выкл.</th>
    <th>Язык</th>
        <? for($x=0;$x<sizeof($block['menus']);$x++): ?> 
        <tr>
            <td><?=$block['menus'][$x]['id']?></td>
            <td><?=$block['menus'][$x]['name']?></td>
            <? if(in_array($block['menus'][$x]['id'], $block['menu_id'])): ?>
                <td>
                    <a href="<?=BASEURL.LANG?>admin/editpageview/menu/<?=$param['params'][2]?>/<?=$param['params'][3]?>/off/<?=$block['menus'][$x]['id']?>">
                        <img src="<?=BASEURL?>images/admin/ico_on.gif" />
                    </a>
                </td>
            <? else: ?>
                <td>
                    <a href="<?=BASEURL.LANG?>admin/editpageview/menu/<?=$param['params'][2]?>/<?=$param['params'][3]?>/on/<?=$block['menus'][$x]['id']?>">
                        <img src="<?=BASEURL?>images/admin/ico_off.gif" />
                    </a>
                </td>
            <? endif; ?>
            <td>
                <select name="lang_id" onchange="location.href='<?=BASEURL.LANG?>admin/editpageview/menu/<?=$param[params][2]?>/<?=$param[params][3]?>/lang/<?=$block[menus][$x][id]?>/'+options[selectedIndex].value;">
                    <option value="0">--</option>
                <? for($y=0;$y<sizeof($lang);$y++): ?>
                    <? if($lang[$y]['id'] == $block['lang_id'][$block['menus'][$x]['id']]): ?>
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