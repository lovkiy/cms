<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header>
        <h3 class="tabs_involved">Выберите модуль из которого барть вид для шаболна <b><?=$tplid?></b> и блока №<?=$block_id?> 
        </h3>
    </header>
    <table class="tablesorter" cellspacing="0"> 
        <thead> 
            <tr> 
                <th>№ Модуля</th> 
    		<th>Название Модуля</th>    		  		
    		<th align="center" >Действие</th> 
            </tr> 
	</thead> 
        <tbody>
        <? for($x=0;$x<sizeof($modules);$x++): ?>
        <tr>
            <td>
                <b><i><?=$modules[$x]['id']?></i></b>
            </td>
            <td>
                <b><i><?=$modules[$x]['name']?></i></b>
                <i><span style="color: mediumslateblue;">(<?=$modules[$x]['description']?>)</span></i>
            </td>
            <td align="center">
                <a href="<?=BASEURL.LANG?>admin/addblock/<?=$tplid?>/<?=$block_id?>/<?=$modules[$x]['id']?>">
                    Добавить
                </a>
            </td>
        </tr>        
        <? endfor; ?>
        </tbody>
    </table>    



<footer></footer>

</article><!-- end of content manager article -->