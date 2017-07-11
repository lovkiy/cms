<?php
/* 
* To change this template, choose Tools | Templates
* and open the template in the editor.
*/

?>

<article class="module width_full">
		<header><h3 class="tabs_involved">Форма редактирования страницы...</h3>		
                    <ul class="tabs">
                        <? for($x=0;$x<sizeof($lang);$x++): ?>
                            <li><a href="#tab<?=$x?>"><?=$lang[$x]['code']?></a></li>                
                        <? endfor; ?> 
                        <li><a href="#tab20">Ссылка страницы</a></li>
                    </ul>
		</header>
            <form action="<?=BASEURL.LANG?>admin/editpage/<?=$page[0][id]?>" method="POST">    
		<div class="tab_container">
                <? for($y=0;$y<sizeof($lang);$y++): ?>
                    <div id="tab<?=$y?>" class="tab_content" style="height: 400px; padding: 20px 20px 0 30px;">                        
			           
                        <p><b><i>Название</i></b></p>
                        <input type="text" name="pages[<?=$lang[$y]['id']?>][name]" value="<?=$page[$y][name]?>" style="width: 95%;" />
                        <p><b><i>Title</i></b></p>
                        <textarea name="pages[<?=$lang[$y]['id']?>][title]" style="width: 95%"><?=$page[$y][title]?></textarea>
                        <p><b><i>Keywords</i></b></p>
                        <textarea name="pages[<?=$lang[$y]['id']?>][keywords]" style="width: 95%"><?=$page[$y][keywords]?></textarea>
                        <p><b><i>Description</i></b></p>
                        <textarea name="pages[<?=$lang[$y]['id']?>][description]" style="width: 95%"><?=$page[$y][description]?></textarea><br />
                    </div>
                <? endfor; ?>
                <div id="tab20" class="tab_content" style="height: 400px; padding: 20px 20px 0 30px;">
                    <p><b><i>Ссылка</i></b></p>
                    <input type="text" name="url" value="<?=$page[0][url]?>" style="width: 80%;" /> 
                </div>
		</div><!-- end of .tab_container -->
    <footer style="text-align: center;">
        <input class="alt_btn" style="margin: 5px 0 0 0;" type="submit" value="Изменить" />
    </footer>
            </form>	    
</article><!-- end of content manager article -->
