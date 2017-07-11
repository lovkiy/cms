<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/
if(!function_exists(menu)){
    function menu($page,$data, $parent = 0){
        $arr = $data[$parent];

        for($i = 0; $i < count($arr); $i++):
            $url = ($arr[$i]['main']) ? BASEURL : BASEURL.LANG.$arr[$i]['url'];?>

            <? if($arr[$i]['url']==$page):?>		
                            <li class="active">
                    <? else: ?>
                            <li>
                    <? endif; ?>
                <div>
                    <a href="<?=$url?>">
                        <span><?//$arr[$i]['img']?></span>
                        <?=$arr[$i]['name']?>
                    </a>
                </div>
                <? if(isset($data[$arr[$i]['id']])):?>
                <ul>
                    <? menu($page,$data, $arr[$i]['id']);?>
                </ul>
                <? endif; ?>
            </li>
        <? endfor; ?>
     <?  }
  } ?>
 
<ul>
    <? menu($page,$menu); ?>
</ul>