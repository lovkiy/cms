<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Выберите вид для шаблона <b><?=$tplid?></b> блока №<?=$block_id?> и модуля №<?=$mod_id?></h3></header>

<form action="<?=BASEURL.LANG?>admin/editlayout/<?=$tplid?>" method="POST">
<table class="tablesorter" cellspacing="0"> 
    <thead> 
        <tr>            
            <th>№</th> 
            <th>Название Вида</th>
            <th></th>
            <th colspan="2">Варианты вывода вида</th> 
        </tr> 
    </thead> 
    <tbody>
    <? for($x=0;$x<sizeof($views);$x++): ?>
        <tr>            
            <td><?=$views[$x]['view']?></td>
            <td><?=$views[$x]['name']?></td>  
            <td><input type="radio" name="view" value="<?=$views[$x]['id']?>" /></td>
            <td><?=$views[$x]['description']?></td>
            <td>
                <ul>
                <? foreach($view_files[$views[$x]['view']] as $file_id=>$file_name): ?>
                    <li>                        
                        <?=$file_name?><input type="radio" name="file_id[<?=$views[$x]['id']?>]" value="<?=$file_id?>" />
                    </li>                    
                <? endforeach; ?>
                </ul>
            </td>
        </tr>
    <? endfor; ?>
    </tbody>
</table> 



<input type="hidden" name="tplname" value="<?=$tplid?>" />
<input type="hidden" name="block" value="<?=$block_id?>" />
<input type="hidden" name="module" value="<?=$mod_id?>" />
<p><b><i>Описание блока вывода:</i></b></p>  
<input type="text" name="description" value="" style="width: 99%;"/><br/><br />
    
<footer style="text-align: center;">
        <input class="alt_btn" style="margin: 5px 0 0 0;" type="submit" value="Добавить" />
    </footer>
</form>

</article><!-- end of content manager article -->
