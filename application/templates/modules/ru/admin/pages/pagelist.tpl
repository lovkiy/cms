<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
//echo "<pre>";
//print_r($pages);
//echo "</pre>";

function page($data, $parent = 0){
    $arr = $data[$parent];

    for($i = 0; $i < count($arr); $i++): ?>  
    <li>
        <table cellspacing=0 cellpadding=0 border=0 width=650>
            <tr>
                <th width="45" align="left">
                 <? if($arr[$i]['type']==1): ?>   
                    <img src="<?=BASEURL?>images/admin/file.gif">
                 <? else: ?>
                    <img src="<?=BASEURL?>images/admin/folder.gif">
                 <? endif; ?>
                </th>
                    <td width="195" align="left"><?=$arr[$i]['name']?></td>
                        <td>
                        <? if($arr[$i]['type']==1): ?>      
                            <? if($arr[$i]['main']==1): ?>                                    
                                <img src="<?=BASEURL?>images/admin/ico_on.gif" />                                   
                            <? else: ?>
                                <a href="<?=BASEURL.LANG?>admin/setmain/<?=$arr[$i]['id']?>">
                                    <img src="<?=BASEURL?>images/admin/ico_off.gif" />
                                </a>
                            <? endif; ?>
                        <? endif; ?>
                        </td>
                        <td width="70">
                        <? if($arr[$i]['type']==1): ?>     
                            <? if($arr[$i]['active']==1): ?>
                                <a href="<?=BASEURL.LANG?>admin/hidepage/<?=$arr[$i]['id']?>">
                                    <img src="<?=BASEURL?>images/admin/ico_on.gif" />
                                </a>
                            <? else: ?>
                                <a href="<?=BASEURL.LANG?>admin/showpage/<?=$arr[$i]['id']?>">
                                    <img src="<?=BASEURL?>images/admin/ico_off.gif" />
                                </a>
                            <? endif; ?>
                        <? endif; ?>
                        </td>
                        <td width="35">
                            <img src="<?=BASEURL?>images/admin/per_down.gif" />                                    
                            <img src="<?=BASEURL?>images/admin/per_up.gif" />
                        </td>
                        <td width="85">
                            <a href="<?=BASEURL.LANG?>admin/movetofolder/<?=$arr[$i]['id']?>" >
                                <img src="<?=BASEURL?>images/admin/perem.gif" />
                            </a>
                        </td>
                        <td width="30">                           
                            <? if($arr[$i]['type']==1): ?>
                                <a href="<?=BASEURL.LANG?>admin/editpage/<?=$arr[$i]['id']?>">
                                    <input type="image" title="Edit" src="<?=BASEURL?>images/admin/icn_edit.png">
                                </a>
                            <? else: ?>
                                <a href="<?=BASEURL.LANG?>admin/editfolder/<?=$arr[$i]['id']?>">
                                    <input type="image" title="Edit" src="<?=BASEURL?>images/admin/icn_edit.png">
                                </a>
                            <? endif; ?>
                        </td>
                        <td width="25">
                        <? if($arr[$i]['main']!=1): ?>
                            <? if($arr[$i]['type']!=1): ?>
                                <a onclick="if (confirm('Вы точно хотите удалить папку?') ) {
                                                if (confirm('Удалить со всеми вложеными страницами?')){
                                                    location.href='<?=BASEURL.LANG?>admin/dellfolderall/<?=$arr[$i][id]?>';
                                                }else{
                                                    location.href='<?=BASEURL.LANG?>admin/dellfolder/<?=$arr[$i][id]?>';
                                                }        
                                             } else { return };">
                                    <input type="image" title="Trash" src="<?=BASEURL?>images/admin/icn_trash.png">  
                                </a>
                            <? else: ?>
                                <a onclick="if (confirm('Вы точно хотите удалить страницу?') ) {
                                                location.href='<?=BASEURL.LANG?>admin/dellpage/<?=$arr[$i][id]?>';
                                             } else { return };">
                                    <input type="image" title="Trash" src="<?=BASEURL?>images/admin/icn_trash.png">  
                                </a>
                            <? endif; ?>
                        <? endif; ?>    
                        </td>
                </tr>    
            </table>
            <ul>
                <? for($x=0;$x<sizeof($arr[$i]['views']);$x++): ?>
                    <li>
                        <a href="<?=BASEURL.LANG?>admin/editpageview/<?=$arr[$i]['views'][$x]['module']?>/<?=$arr[$i]['id']?>/<?=$arr[$i]['views'][$x]['lid']?>/<?=$arr[0]['lang_id']?>">
                            <?=$arr[$i]['views'][$x]['name']?>
                        </a>
                        <? if(!empty($arr[$i]['views'][$x]['description'])):?>
                            &nbsp;(<?=$arr[$i]['views'][$x]['description']?>)
			<? else: ?>
                            &nbsp;
			<? endif; ?>
                    </li>
                <? endfor; ?>
            </ul>
            <? if(isset($data[$arr[$i]['id']])):?>
            <ul>
                <? page($data, $arr[$i]['id']);?>
            </ul>
            <? endif; ?>
        </li>
    <? endfor; 
 } ?>
 
 
<script type="text/javascript">
    $(function() {
        $("#tree").treeview({
            collapsed: true,
            animated: "medium",
            control:"#sidetreecontrol",
            persist: "cookie",
            cookieId: "rememberme"
        });
    })    
</script>
 <article class="module width_full">
    <header>
        <h3 class="tabs_involved">Список страниц проэкта&nbsp;|&nbsp; 
            <a href="<?=BASEURL.LANG?>admin/createpage">Добавить новую страницу</a>&nbsp;|&nbsp;
            <a href="<?=BASEURL.LANG?>admin/addfolder">Добавить папку</a>
        </h3>
    </header>
    
<div id="sidetree">
    
<div class="treeheader">&nbsp;</div>
    
<div style="height:17px; overflow:hidden;">
    <div id="sidetreecontrol">
        <span class="sver">
            <a href="?#">Свернуть всё</a>
        </span>
        <span class="rozver">
            <a href="?#">Развернуть всё</a>
        </span>
    </div>
</div>

 <table cellspacing=0 cellpadding=0 border=0>
    <tr>
        <td width="9" height="9"></td>
        <td height="9"></td>
        <td width="9" height="9"></td>
    </tr>
    <tr>
    	<td width="9"></td>
    	<td style="font-size:12px;">
            <table cellspacing=0 cellpadding=0 border=0 width=650>
                <tr>
                    <th width="45"></th>
                    <th width="195" align="left">Название</th>
                    <th>Главная</th>
                    <th width="70">Вкл./выкл.</th>
                    <th width="35">Сорт.</th>
                    <th width="85">Переместить</th>
                    <th width="30">Ред.</th>
                    <th width="25">Уд.</th>
                </tr>    
            </table>
                <ul id="tree" class="treeview" >
                    <? page($pages); ?>
                </ul>
            </td>
        <td width="9"></td>
    </tr>
    <tr>
        <td width="9" height="9"> 
        </td>
    	<td height="9"></td>
    	<td width="9" height="9"></td>
    </tr>
</table>
<footer></footer>

</article><!-- end of content manager article -->