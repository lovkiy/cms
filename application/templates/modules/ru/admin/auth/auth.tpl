<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
<link type="text/css" rel="stylesheet" href="<?=BASEURL?>css/admin/admin.style.css" />
</head>

<body>
<div id="center">
	<div class="center">
    	<div class="forma">
        	<div class="logo"><a href="http://msoft.ua/" target="_blank"><img src="<?=BASEURL?>images/admin/logo.png" border="0" alt="" /></a></div>
            <div class="iblock error"><?=$error_message?></div>
            <form action="<?=BASEURL.LANG?>admin/auth" method="post" id="log">
            	<label for="login">Логин</label>
                <div class="login"><input type="text" name="user_login" id="login" value="" /></div>
            	<label for="pass">Пароль</label>
                <div class="pass"><input type="password" name="user_password" id="pass" value="" /></div>
                <div class="button">
                	<button type="submit" style="cursor:pointer;">
                    	<img src="<?=BASEURL?>images/admin/form_butt1.png" onmouseover="this.src='<?=BASEURL?>images/admin/form_butt2.png'" onmouseout="this.src='<?=BASEURL?>images/admin/form_butt1.png'" border="0" alt="" />
                    </button>
                </div>
            </form>
        </div>
    </div>
</div>
</body>
</html>
