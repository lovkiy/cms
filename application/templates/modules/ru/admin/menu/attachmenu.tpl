<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Добавление пункта меню</h3></header>

    
<script type="text/javascript">
    $(function() {
        $("#tree").treeview({
            collapsed: false,
            animated: "medium",
            control:"#sidetreecontrol",
            persist: "cookie",
            cookieId: "rememberme"
        });
    })    
</script>

<form action="<?=BASEURL.LANG?>admin/attachmenu/<?=$menu_id?>" method="post">
    <table>
        <tr>
            <td>
                <img src="<?=BASEURL?>images/module_1/perem.gif"/>
            </td>
            <td style="color:#474747; text-transform:uppercase; font-size:13px; font-weight:bold;">Добавление страницы</td>
        </tr>
    </table>
    <table cellspacing=0 cellpadding=0 border=0 width="400">
      	<tr>
            <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_1.gif"/></td>
            <td height="9" background="<?=BASEURL?>images/module_1/ob_2.gif"></td>
            <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_3.gif"/></td>
     	</tr>
       	<tr>
            <td width="9" background="<?=BASEURL?>images/module_1/ob_4.gif"></td>
            <td bgcolor="#f3f3f3" style="font-size:12px;">
            
            <div style='font-size:12px;' class='linck'>
                <ul id='tree'>
                <? for($x=0;$x<sizeof($pages);$x++):?>
                    <li>
                        <input type="checkbox" name="page[<?=$pages[$x]['id']?>][id]" value="<?=$pages[$x]['id']?>" />
                        <?=$pages[$x]['name']?>  
                        <input type="text" name="page[<?=$pages[$x]['id']?>][name]" value="<?=$pages[$x]['name']?>" />
                    </li>
                <? endfor; ?>    
                </ul>
            </div>
    
            </td>
            <td width="9" background="<?=BASEURL?>images/module_1/ob_5.gif"></td>
        </tr>
      	<tr>
            <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_6.gif"/></td>
            <td height="9" background="<?=BASEURL?>images/module_1/ob_7.gif"></td>
            <td width="9" height="9"><img src="<?=BASEURL?>images/module_1/ob_8.gif"/></td>
      	</tr>
    </table>    
    
<footer>
        <input class="alt_btn" type="submit" value="Сохранить" />
    </footer>
</form>

</article><!-- end of content manager article -->