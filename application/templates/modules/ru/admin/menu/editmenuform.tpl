<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/


function page($data, $parent = 0,$menu_id){
    $arr = $data[$parent];

    for($i = 0; $i < count($arr); $i++): ?>  
    <li>
        <table cellspacing=0 cellpadding=0 border=0 class="admintable" width=650>
            <tr>
                <th width="45"><img src="<?=BASEURL?>images/admin/file.gif"></th>
                    <td width="195" align="left"><?=$arr[$i]['name']?></td>
                    <td><?=$arr[$i]['pagename']?></td>
                    <td width="70">                         
                    <? if($arr[$i]['active']==1): ?>
                        <a href="<?=BASEURL.LANG?>admin/hidemenu/<?=$arr[$i]['id']?>">
                            <img src="<?=BASEURL?>images/admin/ico_on.gif" />
                        </a>
                    <? else: ?>
                        <a href="<?=BASEURL.LANG?>admin/showmenu/<?=$arr[$i]['id']?>">
                            <img src="<?=BASEURL?>images/admin/ico_off.gif" />
                        </a>
                    <? endif; ?>
                    </td>
                    <td width="35">
                          <img src="<?=BASEURL?>images/admin/per_down.gif" />                                    
                          <img src="<?=BASEURL?>images/admin/per_up.gif" />
                    </td>
                    <td width="85">
                         <a href="<?=BASEURL.LANG?>admin/movemenu/<?=$menu_id?>/<?=$arr[$i]['id']?>">
                             <img src="<?=BASEURL?>images/admin/perem.gif" />
                         </a>
                    </td>
                    <td width="30">                           
                        <a href="<?=BASEURL.LANG?>admin/editmenupage/<?=$menu_id?>/<?=$arr[$i]['id']?>">
                            <input type="image" title="Edit" src="<?=BASEURL?>images/admin/icn_edit.png">
                        </a>
                    </td>
                    <td width="25">
                        <a href="<?=BASEURL.LANG?>admin/dellmenupage/<?=$menu_id?>/<?=$arr[$i]['id']?>">
                            <input type="image" title="Trash" src="<?=BASEURL?>images/admin/icn_trash.png">
                        </a>
                    </td>
                </tr>    
            </table>
            
            <? if(isset($data[$arr[$i]['id']])):?>
            <ul>
                <? page($data, $arr[$i]['id'],$menu_id);?>
            </ul>
            <? endif; ?>
        </li>
    <? endfor; 
 } ?>












<article class="module width_full">
    <header><h3 class="tabs_involved">Редактирование меню</h3></header>

<script type="text/javascript">
    $(function() {
        $("#tree").treeview({
            collapsed: false,
            animated: "medium",
            control:"#sidetreecontrol",
            persist: "location"
        });
    })
</script>
    
<table cellspacing=0 cellpadding=0 border=0 width="668">
    <tr>
        <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_1.gif"/></td>
        <td height="9" background="<?=BASEURL?>images/module_1/ob_2.gif"></td>
        <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_3.gif"/></td>
    </tr>
    <tr>
        <td width="9" background="<?=BASEURL?>images/module_1/ob_4.gif"></td>
    	<td bgcolor="#f3f3f3" style="font-size:12px;">
      	<form action="<?=BASEURL.LANG?>admin/editmenu/<?=$menu_id?>" method="post">
            <table>
                <tr>
                    <td>Название:</td>
                    <td>
                        <input type="text" name="name" value="<?=$name?>" size=50 />
                    </td>
                    <td><input type="submit" value="Изменить" /></td>
                </tr>
            </table>
        </form>
            <table>
                <tr>
                    <td><a href="<?=BASEURL.LANG?>admin/attachmenu/<?=$menu_id?>">Добавить пункт меню</a> </td>
                </tr>
            </table>
            <table width=650 cellspacing=0 cellpadding=0 border=0>
                <tr>
                    <th bgcolor="#CCCCCC" width="200">Название в меню</th>
                    <th bgcolor="#CCCCCC">Название страницы</th>
                    <th bgcolor="#CCCCCC" width="70">Вкл./выкл.</th>
                    <th bgcolor="#CCCCCC" width="35">Сорт.</th>
                    <th bgcolor="#CCCCCC" width="85">Переместить</th>
                    <th bgcolor="#CCCCCC" width="30">Ред.</th>
                    <th bgcolor="#CCCCCC" width="25">Уд.</th>
                </tr>
            </table>
            <ul id="tree">
                <? page($pages,0,$menu_id); ?>
                
                
                
                
                
                
                
                
  <!--              
                
                
                
                
                
            <? for($x=0;$x<sizeof($pages);$x++): ?>
                <li>
                    <table width=650 cellspacing=0 cellpadding=0 border=0>
                        <tr>
                            <td width="250">
                                <img align="absmiddle" style="margin-right:5px;" src="<?=BASEURL?>images/admin/file.gif">
                                <?=$pages[$x]['name']?>
                            </td>
                            <td><?=$pages[$x]['pagename']?></td>
                            <td width="70">
                                <img border="0" src="<?=BASEURL?>images/admin/ico_on.gif">
                            </td>
                            <td width="35">
                                <img border="0" src="<?=BASEURL?>images/admin/per_down.gif">
                            </td>
                            <td width="80">
                                <a href="<?=BASEURL.LANG?>admin/movemenu/<?=$menu_id?>/<?=$pages[$x]['id']?>">
                                    <img border="0" src="<?=BASEURL?>images/admin/perem.gif">
                                </a>
                            </td>
                            <td width="30">
                                <a href="<?=BASEURL.LANG?>admin/editmenupage/<?=$menu_id?>/<?=$pages[$x]['id']?>">
                                    <img border="0" src="<?=BASEURL?>images/admin/red.gif">
                                </a>                                
                            </td>
                            <td width="30">
                                <a href="<?=BASEURL.LANG?>admin/dellmenupage/<?=$menu_id?>/<?=$pages[$x]['id']?>">
                                    <img border="0" src="<?=BASEURL?>images/admin/del.gif">
                                </a>                                
                            </td>
                        </tr>
                    </table>
                </li>
            <? endfor; ?>
  -->
            </ul>                   
        </td>
        <td width="9" background="<?=BASEURL?>images/module_1/ob_5.gif"></td>
    </tr>
    <tr>
        <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_6.gif"/></td>
        <td height="9" background="<?=BASEURL?>images/module_1/ob_7.gif"></td>
        <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_8.gif"/></td>
    </tr>
</table> 
<footer></footer>

</article><!-- end of content manager article -->