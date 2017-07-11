<section id="secondary_bar">
    <div class="user">
        <p>
            <?=$user_info['user_name']?><!-- (<a href="#">3 Messages</a>)-->
            <a class="logout" href="<?=BASEURL.LANG?>admin/logout">ВЫХОД</a>
        </p>
        <!-- <a class="logout_user" href="#" title="Logout">Logout</a> -->
    </div>
    <div class="breadcrumbs_container">
        <article class="breadcrumbs"><a href="<?=BASEURL.LANG?>admin"><?=SITENAME?></a> <div class="breadcrumb_divider"></div> <a class="current">Dashboard</a></article>
    </div>
</section><!-- end of secondary bar -->
	
	<aside id="sidebar" class="column">
		<h3>Управление контентом</h3>
		<ul class="toggle">						
			<li class="icn_pages"><a href="<?=BASEURL.LANG?>admin/pagelist">Список страниц</a></li>
                        <li class="icn_menus"><a href="<?=BASEURL.LANG?>admin/menulist">Меню</a></li>			
		</ul> 
                <h3>Возможности</h3>
		<ul class="toggle">
			<li class="icn_new_page"><a href="<?=BASEURL.LANG?>admin/catlist">Каталог</a></li>                        
			<li class="icn_pages"><a href="<?=BASEURL.LANG?>admin/orderlist">Заказы</a></li>
                        <li class="icn_pages"><a href="<?=BASEURL.LANG?>admin/newslist">Фильтры</a></li> 
                        <li class="icn_pages"><a href="<?=BASEURL.LANG?>admin/propertylist">Свойства</a></li>
                        <li class="icn_maps"><a href="<?=BASEURL.LANG?>admin/mapslist">Управаление картами</a></li>
                        <li class="icn_gallery"><a href="<?=BASEURL.LANG?>admin/gallerylist">Список галерей</a></li>
                        <li class="icn_gallery"><a href="<?=BASEURL.LANG?>admin/officeuserlist">Список пользователей кабинета</a></li>                                                
			<li class="icn_pages"><a href="<?=BASEURL.LANG?>admin/newslist">Список новостей</a></li>
                        <li class="icn_bimages"><a href="<?=BASEURL.LANG?>admin/bannerlist">Список баннеров</a></li>
                        <li class="icn_bimages"><a href="<?=BASEURL.LANG?>admin/infoblocklist">Инфомодули</a></li>
                        <li class="icn_bimages"><a href="<?=BASEURL.LANG?>admin/infgrplist">Список групп инфомодуля</a></li>
                        <li class="icn_bimages"><a href="<?=BASEURL.LANG?>admin/reviewlist">Список добавленых отзывов</a></li>
		</ul>
                <h3>Настройки</h3>
		<ul class="toggle">
                        <li class="icn_view_users"><a href="<?=BASEURL.LANG?>admin/userslist">Пользователи</a></li>                        
		</ul>
                <h3>Разработка</h3>
		<ul class="toggle">
                        <li class="icn_templates"><a href="<?=BASEURL.LANG?>admin/layouts">Макеты</a></li>
                        <li class="icn_templates"><a href="<?=BASEURL.LANG?>admin/modules">Модули</a></li>			                        
			<li class="icn_wigets"><a href="<?=BASEURL.LANG?>admin/widgetlist">Управление виджетами</a></li>			
		</ul>
		<!--<h3>Резервирование</h3>
		<ul class="toggle">			
			<li class="icn_rezerv"><a href="<?=BASEURL.LANG?>admin/rezervlist">Управление резервами</a></li>			
		</ul>
		<h3>Отзывы</h3>
		<ul class="toggle">			
                        <li class="icn_rewievs"><a href="<?=BASEURL.LANG?>admin/rewievslist">Все отзывы</a></li>			
		</ul>-->                
                
		<footer>
			<hr />
			<p><strong>Copyright &copy; <a target="_blank" href="http://msoft.ua/" style="color:#197994;">MSoft</a>, 2013. Все права защищены.</strong></p>			
		</footer>
	</aside><!-- end of sidebar -->
	
	<section id="main" class="column">