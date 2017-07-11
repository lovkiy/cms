<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Созданные макеты</h3>
        <b style="font-size: 16px;"><a href="<?=BASEURL.LANG?>admin/templates">Добавить макет</a></b>
    </header>
    <table class="tablesorter" cellspacing="0"> 
        <thead> 
            <tr> 
                <th>Id</th> 
    		<th>Название меню</th>    		  		
    		<th colspan="2" align="center" >Действие</th> 
            </tr> 
	</thead> 
	<tbody>
        <? for($x=0;$x<sizeof($layoutlist);$x++):?>
            <tr> 
                <td><?=$menu[$x]['id']?></td> 
    		<td><b><?=$layoutlist[$x]['name']?></b></td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/editlayout/<?=$layoutlist[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_edit.png" title="Edit">
                    </a>
                </td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/dellayout/<?=$layoutlist[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_trash.png" title="Trash">
                    </a>
                </td>    		
            </tr>
        <? endfor; ?>
        </tbody> 
    </table>
    <footer></footer>

</article><!-- end of content manager article -->