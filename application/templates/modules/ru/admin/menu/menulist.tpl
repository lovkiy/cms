<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>

<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Список доступных меню</h3>
        <form action="<?=BASEURL.LANG?>admin/menulist" method="POST">
            <input type="text" name="menuname"/>
            <input class="alt_btn" type="submit" value="Создать" />                  
        </form>
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
        <? for($x=0;$x<sizeof($menu);$x++): ?>
            <tr> 
                <td><?=$menu[$x]['id']?></td> 
    		<td><b><?=$menu[$x]['name']?></b></td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/editmenu/<?=$menu[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_edit.png" title="Edit">
                    </a>
                </td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/dellmenu/<?=$menu[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_trash.png" title="Trash">
                    </a>
                </td>    		
            </tr>
        <? endfor; ?>
        </tbody> 
    </table>
    <footer></footer>

</article><!-- end of content manager article -->