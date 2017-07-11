<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Управление виджетами&nbsp;|&nbsp;
            <a href="<?=BASEURL.LANG?>admin/createwidget">Создать виджет</a>
        </h3>        
    </header>
    <table class="tablesorter" cellspacing="0"> 
        <thead> 
            <tr> 
                <th>Id</th> 
    		<th>Название виджета</th>    		  		
    		<th colspan="2" align="center" >Действие</th> 
            </tr> 
	</thead> 
	<tbody>
        <? for($x=0;$x<sizeof($widgets);$x++): ?>
            <tr> 
                <td><?=$widgets[$x]['id']?></td> 
    		<td><?=$widgets[$x]['name']?></td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/editwidget/<?=$widgets[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_edit.png" title="Edit">
                    </a>
                </td> 
    		<td>
                    <a href="<?=BASEURL.LANG?>admin/dellwidget/<?=$widgets[$x]['id']?>">
                        <input type="image" src="<?=BASEURL?>images/admin/icn_trash.png" title="Trash">
                    </a>
                </td>    		
            </tr>
        <? endfor; ?>
        </tbody> 
    </table>
    <footer></footer>

</article><!-- end of content manager article -->       
