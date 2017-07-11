<?php
/* 
* TODO: Нужно написать ява функцию проверки выбронности 
* баттона, чтобы не гонять пустых постов....
*/

?>
<article class="module width_full">
    <header><h3 class="tabs_involved">Создание страницы проэкта...</h3></header>


<form action="<?=BASEURL.LANG?>admin/createpage" method="POST"  onsubmit="if (document.getElementById('page_name').value ==''){alert('Вы не ввели название страницы!'); return false}">
    <p><b><i>Название станицы(Не больше 100 симфолов):</i></b></p>
    <input type="text" name="name" id='page_name' style="width: 80%;" />
    <br /><hr />
    <p><b><i>Выберите макет на базе которого будет создана страница:</i></b></p>
<? foreach($list as $key=>$layout): ?>
    <input type="radio" name="layout" value="<?=$layout['id']?>" />
    <?=$layout['name']?><br />
<? endforeach; ?>
    <footer style="text-align: center;">
        <input style="margin: 5px 0 0 0;" class="alt_btn" type="submit" value="Создать страницу" />
    </footer>
</form>

</article><!-- end of content manager article -->