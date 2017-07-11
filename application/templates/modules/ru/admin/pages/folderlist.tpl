<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
//echo "<pre>";
//print_r($folders);
//echo "</pre>";
?>
<h3>Список папок</h3>
<a href="<?=BASEURL.LANG?>admin/movetofolder/<?=$page?>/0" >Корень</a><br />
<? for($x=0;$x<sizeof($folders);$x++): ?>
    <a href="<?=BASEURL.LANG?>admin/movetofolder/<?=$page?>/<?=$folders[$x]['id']?>" ><?=$folders[$x]['name']?></a><br />

<? endfor; ?>
