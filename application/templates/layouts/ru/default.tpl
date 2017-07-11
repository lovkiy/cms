<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<?=$meta?>
<script type="text/javascript" src="<?=BASEURL?>js/jquery.js"></script>
<script type="text/javascript" src="<?=BASEURL?>js/jqueryslidemenu.js"></script>
<script type="text/javascript" src="<?=BASEURL?>ajax/cart/ajax.js"></script>
<style type="text/css">
body {
	margin: 0px;
	background-color: #FFF;
}
body,td,th {
	font-family: Arial, Helvetica, sans-serif;
	font-size: 12px;
	color: #000;
}
#wrapper {width:980px; margin:0 auto;}


#up-content {width:auto; height:331px; position:relative;}
#logotipe {position:absolute; top:20px; left:0;}
#contacts {position:absolute; top:20px; right:0; text-align:right; color:#999; font-weight:bold; padding:10px 0;}
#contacts span {font-size:23px; color:#6a9574; font-weight:normal;}
#up-image {position:absolute; width:auto; height:200px; bottom:32px;}
.clear {clear:both;}


.jqueryslidemenu {position:absolute; background:#c6e9d1; bottom:0px; width:980px;}
.jqueryslidemenu ul{list-style:none; margin:0; padding:0; height:31px; padding-left:20px;}
.jqueryslidemenu ul img {display:none;}
.jqueryslidemenu ul li{position: relative; float:left; background-image:url(<?=BASEURL?>images/menu.gif); background-repeat:no-repeat; background-position:top right;}
.jqueryslidemenu ul li a{color:#467350; font-size:12px; text-transform:uppercase; text-decoration:none; padding:0 12px; line-height:31px; display:block;
background-image:url(<?=BASEURL?>images/menu1.gif); background-repeat:no-repeat; background-position:left; font-weight:bold;}
.jqueryslidemenu ul li a:hover{color:#fff; font-size:12px; text-transform:uppercase; text-decoration:none; padding:0 12px; background-color:#6a9574; display:block; background-image:url(<?=BASEURL?>images/menu2.gif);}
.jqueryslidemenu ul li ul{position:absolute; left:0; top:31px; display:block; visibility:hidden; border:0; padding-left:0px !important;}
.jqueryslidemenu ul li ul img {display:block;}
.jqueryslidemenu ul li ul li{position:relative; background-image:none; display:block; float:none;}
.jqueryslidemenu ul li ul li ul{top: 0;}
.jqueryslidemenu ul li ul li a{color:#467350; display:block; font-size:11px; text-transform:uppercase; text-decoration:none; margin:0; padding:0 8px; line-height:23px; background-color:#c6e9d1; background-image:none !important; font-weight:bold;}
.jqueryslidemenu ul li ul li a:hover{color:#fff; display:block; font-size:11px; text-transform:uppercase; text-decoration:none; margin:0; padding:0 8px; line-height:23px; background-color:#6a9574;}


#center-content {padding:15px 0;}
#side1 {float:left; width:250px; padding:15px; background-color:#24585b; text-align:left;}
#center {float:left; padding-left:20px; width:680px; min-height:300px; text-align:justify;}
.h1 {font-family:'Arial Narrow'; font-size:19px; text-transform:uppercase; margin:0; padding:0 0 15px 20px; color:#6a9574;}


#footer {width:auto; padding:15px; background-color:#24585b;}
#counters {padding:20px 0; text-align:center;}


.jqueryslidemenu2 {margin:0 auto; text-align:center;}
.jqueryslidemenu2 ul {display:inline-block; list-style-type:none; margin:0; padding:0; border-left:solid 1px #093335; border-right:solid 1px #457f82;}
.jqueryslidemenu2 ul li {float:left; text-align:left; padding:0 15px; border-left:solid 1px #457f82; border-right:solid 1px #093335;}
.jqueryslidemenu2 ul li a {font-size:13px; font-weight:bold; color:#c6e9d1; text-decoration:none;}
.jqueryslidemenu2 ul li a:hover {font-size:13px; font-weight:bold; color:#fff; text-decoration:none;}
.jqueryslidemenu2 ul li ul {padding:5px 5px 0 5px; display:none;}
</style>
</head>

<body>
<div id="wrapper">
	<div id="up-content">
		<div id="logotipe"><a href="/"><img src="<?=BASEURL?>images/logotipe.png" width="253" height="60" border="0" /></a></div>
	  <div id="contacts">Контактная информация<br />+38 (000)<span> 000-00-00</span></div>
        <div id="up-image"><img src="<?=BASEURL?>images/up-image.gif" width="980" height="200" /></div>
        <div id="up-menu" class="jqueryslidemenu">
            <?=$block2?>
        </div>
        <div class="clear"></div>
	</div>
    <div id="center">       	
          <?=$block1?>
    </div>
    <div id="side2"></div>
    <div class="clear"></div>
</div>
<div id="footer">
	<div id="dw-menu" class="jqueryslidemenu2">
		<?=$block3?>
    </div>
</div>
<div id="counters">
    	<a href="http://ukrmisto.net/" target="_blank"><img src="http://ukrmisto.net/logo_um.gif" alt="Р�РЅС„РѕСЂРјР°С†РёРѕРЅРЅС‹Р№ РїРѕСЂС‚Р°Р» РіРѕСЂРѕРґРѕРІ РЈРєСЂР°РёРЅС‹ - UKRMISTO" border="0" height="31" width="88"></a>
        <a href="http://www.msoft.com.ua" target="_blank"><img src="http://www.msoft.com.ua/msoft2.gif" alt="Р Р°Р·СЂР°Р±РѕС‚РєР° Рё РїСЂРѕРґРІРёР¶РµРЅРёРµ СЃР°Р№С‚РѕРІ. Р РµРєР»Р°РјР° РІ Р�РЅС‚РµСЂРЅРµС‚Рµ." border="0"></a>
</div>
<div class="clear"></div>

</body>
</html>
