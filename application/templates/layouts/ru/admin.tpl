<!doctype html>
<html lang="ru">

<head>
	<meta charset="utf-8"/>
	<title>Панель управления сайтом - M-CMS <?=SITENAME?></title>
	
	<link rel="stylesheet" href="<?=BASEURL?>css/admin/layout.css" type="text/css" media="screen" />
        <link rel="stylesheet" type="text/css" href="<?=BASEURL?>scripts/treeview/jquery.treeview.css" />
	<link rel="stylesheet" type="text/css" href="<?=BASEURL?>scripts/treeview/red-treeview.css" />
        <link rel="stylesheet" type="text/css" href="<?=BASEURL?>scripts/JSCal2/css/jscal2.css" />
	<link rel="stylesheet" type="text/css" href="<?=BASEURL?>scripts/JSCal2/css/gold/gold.css" />
	<link rel="stylesheet" type="text/css" href="<?=BASEURL?>scripts/JSCal2/css/border-radius.css" />
	<!--[if lt IE 9]>
	<link rel="stylesheet" href="<?=BASEURL?>css/admin/ie.css" type="text/css" media="screen" />
	<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
	<![endif]-->
	<script src="<?=BASEURL?>js/admin/jquery-1.5.2.min.js" type="text/javascript"></script>
	<script src="<?=BASEURL?>js/admin/hideshow.js" type="text/javascript"></script>
	<script src="<?=BASEURL?>js/admin/jquery.tablesorter.min.js" type="text/javascript"></script>
	<script type="text/javascript" src="<?=BASEURL?>js/admin/jquery.equalHeight.js"></script>
        
        <script src="<?=BASEURL?>scripts/treeview/lib/jquery.cookie.js" type="text/javascript"></script>
        <script src="<?=BASEURL?>scripts/treeview/jquery.treeview.js" type="text/javascript"></script>
        <script type="text/javascript" src="<?=BASEURL?>scripts/tinymce/tinymce.min.js"></script>
        <script type="text/javascript" src="<?=BASEURL?>scripts/JSCal2/js/jscal2.js"></script>
	<script type="text/javascript" src="<?=BASEURL?>scripts/JSCal2/js/lang/ru.js"></script>
        
        
        
        
	<script type="text/javascript">
	$(document).ready(function() 
    	{ 
      	  $(".tablesorter").tablesorter(); 
   	 } 
	);
	$(document).ready(function() {

            var str = document.URL.split("#")[1];
          
            if(str){
                // Если введен якорь в строку запросса...
                $("ul.tabs li").removeClass("active"); //Remove any "active" class
		$("li a[href='#"+str+"']").parent().addClass("active"); //Add "active" class to selected tab
		$(".tab_content").hide(); //Hide all tab content

		//var activeTab = $(this).find("a").attr("href"); //Find the href attribute value to identify the active tab + content
		var activeTab = '#'+str;
                $(activeTab).fadeIn(); //Fade in the active ID content                
                
            }else{
                //When page loads...
                $(".tab_content").hide(); //Hide all content
                $("ul.tabs li:first").addClass("active").show(); //Activate first tab
                $(".tab_content:first").show(); //Show first tab content
            }
	

	//On Click Event
	$("ul.tabs li").click(function() {

		$("ul.tabs li").removeClass("active"); //Remove any "active" class
		$(this).addClass("active"); //Add "active" class to selected tab
		$(".tab_content").hide(); //Hide all tab content

		var activeTab = $(this).find("a").attr("href"); //Find the href attribute value to identify the active tab + content
		
                $(activeTab).fadeIn(); //Fade in the active ID content
		return false;
	});

});
//tinymce.PluginManager.load('moxiemanager', '/js/moxiemanager/plugin.min.js');
    tinymce.init({
                //selector: "#elm0 #elm1 #elm2 #elm3 #elm4 #elm5", 
                mode : "exact",
                elements : "elm0,elm1,elm2,elm3,elm4,elm5",
                language : "ru",        
                plugins: [  "advlist autolink lists link image charmap print preview anchor",
                            "searchreplace visualblocks code fullscreen",
                            "insertdatetime media table contextmenu paste jbimages"
                            ],
                toolbar: "alignleft aligncenter alignright alignjustify | bullist numlist outdent indent | link image jbimages fontselect fontsizeselect",
                relative_urls: false,
                autosave_ask_before_unload: false,
                max_height: 500,
                min_height: 160,
                height : 180
    }); 

    </script>
    <script type="text/javascript">
    $(function(){
        $('#sidebar').equalHeight();
    });
</script>
<!--

  <script type="text/javascript" src="<?=BASEURL?>scripts/xinha/XinhaLoader.js?lang=ru&skin=silva"></script>
  <script type="text/javascript">
    _editor_icons = "Tango" // You can pass arguments via the script URL or embed them here.
  </script>
  <script type="text/javascript" src="<?=BASEURL?>scripts/xinha/XinhaConfig.js"></script>
-->
</head>


<body>

	<header id="header">
		<hgroup>
			<h1 class="site_title"><a href="<?=BASEURL.LANG?>/admin"><img src="<?=BASEURL?>images/admin/logo.png" border="0" alt=""></a></h1>
			<h2 class="section_title">Панель управления сайтом (<?=SITENAME?>)</h2>
			<div class="btn_view_site"><a href="/" target="_blank"><img src="<?=BASEURL?>images/admin/on_site1.png" onmouseover="this.src='<?=BASEURL?>images/admin/on_site2.png'" onmouseout="this.src='<?=BASEURL?>images/admin/on_site1.png'" alt="" border="0" /></a></div>
		</hgroup>
	</header> <!-- end of header bar -->
	<div id="allcenter">
	
	
		
		
         <?=$block1?>
         
         
         
         
         
	
	</section>
	</div>


</body>

</html>