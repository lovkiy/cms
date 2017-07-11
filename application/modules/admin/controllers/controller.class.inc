<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
      if ( ! defined('LIC')  ) exit('Не нужно было этого делать..'); 	

/**
 * Котроллер административного кабинета 
 * TODO: нужно сделать управление всеми функциями 
 * CMS из одного модуля и не разносить настройки 
 * по разным модулям для упрощения контроля верисии
 * и лудшей понимаемости 
 * 
 * ЗЫ: Это лично мое мнение но лудше чтобы админка была единым
 * целым исходя из личного опыта... :-)
 *
 * @author Alex
 */
class admin {
 
    public function displayModule($view,$vid=NULL,$param=NULL){  
        
      
        if(!isset($_SESSION['user_admin_id'])):
            
            switch($param['params'][0]):
                case 'auth': 
                    require_once MODULES.'admin/models/authmodel.class.inc';
                    $auth= new authmodel();
                    $data = $auth->cheak($_POST);
                    
                    if(isset($data['user_admin_id'])):
                        $_SESSION['user_admin_id'] = $data['user_admin_id']; 
                        $_SESSION['user_tpl'] = $data['user_tpl'];
                        $data = $this->_userMenu($view, $vid, $param);
                    else:
                        Display::view($data, 'modules/'.LANGDIR.'/admin/auth/auth');
                        exit;
                    endif;                  
                    break;
                default:
                    Display::view('', 'modules/'.LANGDIR.'/admin/auth/auth');
                    exit;
                    break;
            endswitch;
        else:
            switch ($param['params'][0]):
                case 'logout':
                    unset($_SESSION['user_admin_id'],$_SESSION['user_tpl']);
                    Display::view($data, 'modules/'.LANGDIR.'/admin/auth/auth');
                    exit;
                    break;
                default:
                    $data = $this->_userMenu($view, $vid, $param);
                    break;
            endswitch;
            
        endif;
        
        return $data;
    }
    private function _userMenu($view,$vid=NULL,$param=NULL){
        
        require_once MODULES.'admin/models/authmodel.class.inc';
        $auth= new authmodel();
        
        /*
         * Здесь осуществляется загрузка менюхи 
         */ 
        $user = $_SESSION['user_tpl'];
        $user['user_info'] = $auth->user_info($_SESSION['user_admin_id']);
        $data = Display::view($user,'modules/'.LANGDIR.'/admin/auth/menu' , TRUE); 
        
        /*
         * Вывод основных модулей, и подключение ключевых моделей...
         */
        
        switch($param['params'][0]):
            //--------------------------------Управление макетами------------------------
            case 'dellayout': //------------Удаление макета
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                $layout->delLayout($param['params'][1]);
                
                $list['layoutlist'] = $layout->layoutList();
                $data.= Display::view($list, 'modules/'.LANGDIR.'/admin/layout/layouts', TRUE);
                break;
            case 'editlayout': //-----------Редактирование макета------------------------
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();                
               
                    if($_POST):                    
                        $data.= $layout->editLayout($_POST)."<br />";                     
                    endif;
                    
                    $list = $layout->genLable($param['params'][1]);
                    $tpl =  $layout->getTpl($param['params'][1]);                  
                    
                    $data.= Display::view($list, 'layouts/'.LANGDIR.'/'.$tpl,TRUE);
               
                break;
            case 'ceratelayout': //---------Создание макета------------------------------
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                
                $lay_id = $layout->createLayout($_POST);
                
                $list = $layout->genLable($lay_id);              
                $data.= Display::view($list, 'layouts/'.LANGDIR.'/'.$_POST['layout'], TRUE);
                break;
            case 'templates': //------------Просмотр шаблонов перед созданием макета------
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                $list['templatelist'] = $layout->templateList();
                $data.= Display::view($list, 'modules/'.LANGDIR.'/admin/layout/templates', TRUE);
                break;
            case 'layouts': //-------------Список созданных макетов----------------------
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();                
                $list['layoutlist'] = $layout->layoutList();
                $data.= Display::view($list, 'modules/'.LANGDIR.'/admin/layout/layouts', TRUE);
                break;
            case 'addblock': //------------Добавление блоков в шаблон--------------------
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                $list['block_id'] = $param['params'][2];
                $list['tplid'] = $param['params'][1];
                if(isset($param['params'][3])):
                    $list['mod_id'] = $param['params'][3];
                    $list['view_files'] = $layout->getViewsFiles($param['params'][3]);
                    $list['views'] = $layout->getViewslist($param['params'][3]);
                    $data.= Display::view($list, 'modules/'.LANGDIR.'/admin/layout/viewslist', TRUE);
                else:
                    $list['modules'] = $layout->getModulelist();
                    $data.= Display::view($list, 'modules/'.LANGDIR.'/admin/layout/modulelist', TRUE);
                endif;
                break;
            case 'dellview':
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                
                $layout->dellView($param['params'][2]);
                header("Location:".BASEURL.LANG."admin/editlayout/".$param['params'][1]);
                break;
            //------------------------------------------------Управление пользователями ----------------------------------------------
            case 'usertpllist': //--------------------Список шаблонов пользователей---------------------------------------------
                require_once MODULES.'admin/models/usersmodel.class.inc';
                $usertpl = new usersmodel();
                $views['tpls'] = $usertpl->getUserTpl();
                $data.=Display::view($views, 'modules/'.LANGDIR.'/admin/users/usertpllist', TRUE);
                break;
            case 'createusertpl': //-------------------Создание шаблона пользователя------------------------------------
                require_once MODULES.'admin/models/usersmodel.class.inc';
                $usertpl = new usersmodel();
                $views['views'] = $usertpl->getModulesViews();                
               
                if($_POST):
                   $views['message'] = $usertpl->createUserTpl($_POST); 
                endif;
                
                $data.=Display::view($views, 'modules/'.LANGDIR.'/admin/users/createusertpl', TRUE);
                unset($usertpl);
                break;    
            case 'edituser': //-----------------------Редактирование карточки пользователя------------------------------
                if($_POST):
                    $auth->updateUser($_POST,$param['params'][1]);
                    header('Location: '.BASEURL.LANG.'/admin/userslist');                   
                endif;
                
                $userInfo = $auth->user_info($param['params'][1]);               
                $data.= Display::view($userInfo, 'modules/'.LANGDIR.'/admin/users/edituser', TRUE);
                break;    
            case 'userslist': //-----------------------Список пользователей------------------------------------
                $user_list['userslist'] =  $auth->usersList();
                $data.= Display::view($user_list, 'modules/'.LANGDIR.'/admin/users/userslist', TRUE);
                unset($user_list);
                break;
            case 'createuser': //---------------------Создание пользователя по выбранному шаблону----------------
                require_once MODULES.'admin/models/usersmodel.class.inc';
                $usertpl = new usersmodel();
                
                if($_POST):
                   $post = $_POST;                  
                   $result = $auth->createUser($post);
                   
                   if($result['error']):
                      header('Location: '.BASEURL.LANG.'/admin/createuser');
                   endif;
                   $result['post'] = $post;
                endif; 
                $result['userstpl'] = $usertpl->getUserTpl();
                
                $data.= Display::view($result, 'modules/'.LANGDIR.'/admin/users/createuser', TRUE);
                break;
            //---------------------------------Управление страницами проэкта --------------------------------------------------------
            case 'createpage'://---------------Создание страницы проэкта по выбранному шаблону----------------------------- 
                if($_POST):
                    require_once MODULES.'admin/models/pagesmodel.class.inc';
                    $page = new pagesmodel();    
                    $page->createPage($_POST);
                endif;
                
                require_once MODULES.'admin/models/layoutsmodel.class.inc';
                $layout = new layoutsmodel();
                $layoutlist['list'] = $layout->layoutList();
                $data.= Display::view($layoutlist, 'modules/'.LANGDIR.'/admin/pages/createpage', TRUE);
                unset($layout,$layoutlist);
                break;
            case 'pagelist': //--------------------Список страниц исключая страницы админ панели----------------------------
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                
                $pagelist['pages'] = $page->pageList();                
                $data.= Display::view($pagelist, 'modules/'.LANGDIR.'/admin/pages/pagelist', TRUE);
                unlink($pagelist);
                break;           
           
            case 'setmain':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                
                $page->setMain($param['params'][1]);
                
                $pagelist['pages'] = $page->pageList();                
                $data.= Display::view($pagelist, 'modules/'.LANGDIR.'/admin/pages/pagelist', TRUE);
                unlink($pagelist);
                break;
            case 'editpage':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                
                if($_POST){
                  //  if($_POST['base']){
                        $page->updatePage($param['params'][1]);
                 //   }elseif($_POST['meta']){
                    //    $page->updateMeta($param['params'][1]);
                 //   }
                }
                
                $temp = $page->getPageInfo($param['params'][1]);
                $temp['lang'] = $page->getLang();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/pages/editpageform', TRUE);
                unlink($page,$temp);
                break;
            case 'hidepage':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                
                $page->hidePage($param['params'][1]);
                
                header("Location: ".BASEURL.LANG."admin/pagelist");
                break;
            case 'showpage':               
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
               
                $page->showPage($param['params'][1]);
                
                header("Location: ".BASEURL.LANG."admin/pagelist");
                break;
            case 'addfolder':               
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                if($_POST):
                    $page->createFolder($param['params'][1]);                
                    header("Location: ".BASEURL.LANG."admin/pagelist");
                endif;
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/pages/createfolder', TRUE);
                break;
             
            case 'movetofolder':               
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                if(isset($param['params'][2])):                   
                    $page->moveToFolder($param['params'][1],$param['params'][2]);                
                    header("Location: ".BASEURL.LANG."admin/pagelist");
                endif;
                $temp['page'] = $param['params'][1];
                $temp['folders'] = $page->folderList($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/pages/folderlist', TRUE);
                unset($temp,$page);
                break;  
            case 'dellfolder':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                $page->dellFolder($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/pagelist");
                break;
            case 'dellfolderall':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                $page->dellFolderAll($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/pagelist");
                break;
            case 'dellpage':
                require_once MODULES.'admin/models/pagesmodel.class.inc';
                $page = new pagesmodel();
                $page->dellPage($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/pagelist");
                break;
            //-----------------------------------------------Данный метод управляет подгрузкой нужных моделей --------------
            case 'editpageview':
                $data.= $this->_blockEdit($param['params'][1],$param);
                break;
            //----------------------------------------------Управление менюхами----------------------------------------
            case 'menulist':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                if($_POST):
                  $menu->createMenu($_POST['menuname']);
                endif;
                
                $temp['menu'] = $menu->menuList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/menulist', TRUE);
                unset($menu);
                break;
            case 'editmenu':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                if($_POST):
                    $menu->updateMenu($param['params'][1], $_POST['name']);                    
                endif;
                
                $temp['name'] = $menu->getMenuName($param['params'][1]);
                $temp['pages'] = $menu->getPageInMenu($param['params'][1]);
                $temp['menu_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/editmenuform', TRUE);
                unset($menu,$temp);
                break;
            case 'attachmenu':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                if($_POST):
                   $menu->addPageInMenu($param['params'][1]);
                   header("Location: ".BASEURL.LANG."admin/editmenu/".$param['params'][1]); 
                endif;
                
                $temp['pages'] = $menu->getPageForMenu();
                $temp['menu_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/attachmenu', TRUE);
                unset($menu,$temp);
                break;
            case 'dellmenupage':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                $menu->dellFromMenu($param['params'][2]);
                
                $temp['name'] = $menu->getMenuName($param['params'][1]);
                $temp['pages'] = $menu->getPageInMenu($param['params'][1]);
                $temp['menu_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/editmenuform', TRUE);
                unset($menu,$temp);
                break;
            case 'editmenupage':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                if($_POST):
                    $menu->updatePageMenu($param['params'][2], $_POST['pagename']);
                    header("Location: ".BASEURL.LANG."/admin/editmenu/".$param['params'][1]);
                endif;
                
                $temp['page'] = $menu->getMenuPage($param['params'][2]);
                $temp['menu_id'] = $param['params'][1];
                $temp['page_id'] = $param['params'][2];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/editmenupageform', TRUE);
                unset($menu,$temp);
                break;
            case 'movemenu':
                require_once MODULES.'admin/models/menumodel.class.inc';
                $menu = new menumodel();
                
                if(isset($param['params'][3])):                   
                    $menu->moveMenuPage($param['params'][2],$param['params'][3]);                
                    header("Location: ".BASEURL.LANG."admin/editmenu/".$param['params'][1]);
                endif;
                
                $temp['menu_id'] = $param['params'][1];
                $temp['id_moved'] = $param['params'][2];
                $temp['menupagelist'] = $menu->menuPagesList($param['params'][1], $param['params'][2]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/menu/menupagelist', TRUE);
                unset($menu,$temp);
                break;
//------------------------------------------------Управление виджетами  -------------------------------------------
            case 'createwidget':
                require_once MODULES.'admin/models/widgetsmodel.class.inc';
                $widget = new widgetsmodel();
                
                if($_POST):
                    $widget->createWidget();
                    header("Location: ".BASEURL.LANG."admin/widgetlist");
                endif;
                
                $temp['action'] = $param['params'][0];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/widgets/createwidget', TRUE);
                unset($widget,$temp);
                break;
            case 'widgetlist':
                require_once MODULES.'admin/models/widgetsmodel.class.inc';
                $widget = new widgetsmodel();
                
                $temp['widgets'] = $widget->widgetList();
                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/widgets/widgetlist', TRUE);
                unset($widget,$temp);
                break;
            case 'editwidget':
                require_once MODULES.'admin/models/widgetsmodel.class.inc';
                $widget = new widgetsmodel();
                
                if($_POST):
                    $widget->updateWidget($param['params'][1]);
                endif;
                
                $temp = $widget->widgetInfo($param['params'][1]);
                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/widgets/editwidget', TRUE);
                unset($widget,$temp);
                break;
                
    //-------------------------------------------Управление модулями -----------------------------------------------------            
            case 'modules':
                require_once MODULES.'admin/models/modulemodel.class.inc';
                $module = new modulemodel();
                 $temp['message'] = "<h4 class='alert_warning'>Удаление и изминение настроек может привести к потере работоспособности сайта !</h4>";
                
                switch($param['params'][2]):
                    case 'install':
                        require_once MODULES.'admin/models/settingsmodel.calss.inc';
                        $setting = new settingsmodel();
                        $module_name = $setting->getModuleName($param['params'][1]); 
                        if(file_exists(INSTALL.$module_name.'/install.php')):
                            require_once INSTALL.$module_name.'/install.php';
                            $install = $module_name.'_install';
                            if($install()):
                                $temp['message'] = "<h4 class='alert_success'>Модуль успешно установлен !</h4>";
                            else:
                                $temp['message'] = "<h4 class='alert_error'>Произошли ошибки в процессе установки ... </h4>";
                            endif;                            
                        else:
                            $temp['message'] = "<h4 class='alert_error'>Данный модуль отсуцтвует в папке INSTALL ...</h4>";
                        endif;                        
                        break;
                    case 'uninstall':
                        $temp['message'] = "<h4 class='alert_info'>Данная функция в процессе разработки...</h4>";
                        break;
                endswitch;
                
               
                $temp['modulelist'] = $module->getmoduleList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/modules/modulelist', TRUE);
                break;
            case 'settings':
                require_once MODULES.'admin/models/settingsmodel.calss.inc';
                $setting = new settingsmodel();
                
                if($_POST):
                    $setting->updateSettings($param['params'][1]);
                endif;
                
                $temp['settings'] = $setting->getSettings($param['params'][1]);
                $temp['module_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/modules/settingstable', TRUE);
                break; 
   //---------------------------------------------Управление галереями----------------------------------------------------
                
                
            case 'gallerylist':
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                if($_POST):
                    $gallery->createGallery($_POST['name']);
                endif;
                
                $temp['gallery'] = $gallery->getGalleryList();
                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/gallery/gallerylist', TRUE);
                unset($gallery,$temp);
                break;
            case 'dellgallery':
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                $gallery->dellGallery($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/gallerylist");
                break;
            case 'imagelist':
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                if($param['params'][2]=='up'):
                    $gallery->sortUp($param['params'][1],$param['params'][3]);
                elseif($param['params'][2]=='dwn'):    
                    $gallery->sortDwn($param['params'][1],$param['params'][3]);
                endif;
                
                $temp['images'] = $gallery->imageList($param['params'][1]);
                $temp['gal_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/gallery/imagelist', TRUE);
                unset($gallery,$temp);
                break;
            case 'addimage':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                if($_POST):                  
                    $gallery->addImage($param['params'][1]); 
                endif;
                $temp['gal_id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/gallery/addimage', TRUE);
                unset($gallery,$temp);
                break;
            case 'editgallery':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
             
                if($_POST):
                   $gallery->updateGallery($param['params'][1]);
                endif;
                
                $temp = $gallery->getGalleryInfo($param['params'][1]);
                $temp['id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/gallery/editgallery', TRUE);
                unset($gallery,$temp);
                break;
            case 'editimage':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                
                if($_POST):
                    $gallery->updateImage($param['params'][1]);
                endif;
                
                $temp = $gallery->getImageInfo($param['params'][1]);
                $temp['id'] = $param['params'][1];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/gallery/editimage', TRUE);
                unset($gallery);
                break;
            case 'dellimage':              
                require_once MODULES.'admin/models/gallerymodel.class.inc';
                $gallery = new gallerymodel();
                
                $gallery->dellImage($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/imagelist/".$param['params'][2]);
                unset($gallery);
                break;
//-------------------------------------------------Управлениее картами --------------------------------------------------
            case 'mapslist':
                require_once MODULES.'admin/models/mapsmodel.class.inc';
                $map = new mapsmodel();
                
                if($_POST):
                    $map->updateMaps();
                endif;
                
                $temp['maps'] = $map->getMaps();              
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/maps/mapslist', TRUE);
                unset($map,$temp);
                break;    
//-------------------------------------------------Упрвление новостями----------------------------------------------------
            case 'addnewform':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/newsmodel.class.inc';
                $news = new news();
                if($_POST):
                    $news->addNew();
                endif;
                
                $temp['lang'] = $news->getLang(); 
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/news/addnewblock', TRUE);
                unset($temp,$news);
                break;
            case 'dellnew':
                require_once MODULES.'admin/models/newsmodel.class.inc';
                $news = new news();
                $temp['news'] = $news->dellNew($param['params'][1]);
                $temp['news'] = $news->newsList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/news/newslistblock', TRUE);
                unset($temp,$news);
                break;            
            case 'editnewform':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/newsmodel.class.inc';
                $news = new news();
                
                if($_POST):
                    $news->editNew($param['params'][1]);
                endif;
                $temp['news'] = $news->editnewForm($param['params'][1]);
                $temp['lang'] = $news->getLang();    
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/news/editnewblock', TRUE);
                unset($temp,$news);
                break;            
            case 'newslist':
                require_once MODULES.'admin/models/newsmodel.class.inc';
                $news = new news();
                $temp['news'] = $news->newsList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/news/newslistblock', TRUE);
                unset($temp,$news);
                break;
//-------------------------------------------------Упрвление бронированием----------------------------------------------------
            case 'rezervlist':
                require_once MODULES.'admin/models/rezervlist.class.inc';
                $rezerv = new rezerv();
                $temp['rezerv'] = $rezerv->rezervList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/rezerv/rezervlist', TRUE);
                unset($temp,$rezerv);
                break;
            case 'delrezerv':
                require_once MODULES.'admin/models/rezervlist.class.inc';
                $rezerv = new rezerv();
                $temp['rezerv'] = $rezerv->delRezerv($param['params'][1]);
                $temp['rezerv'] = $rezerv->rezervList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/rezerv/rezervlist', TRUE);
                unset($temp,$rezerv);
                break;
            case 'confrezerv':
                require_once MODULES.'admin/models/rezervlist.class.inc';
                $rezerv = new rezerv();
                $temp['rezerv'] = $rezerv->confRezerv($param['params'][1]);
                $temp['rezerv'] = $rezerv->rezervList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/rezerv/rezervlist', TRUE);
                unset($temp,$rezerv);
                break;
            case 'cleanrezerv':
                require_once MODULES.'admin/models/rezervlist.class.inc';
                $rezerv = new rezerv();
                $temp['rezerv'] = $rezerv->cleanRezarv($param['params'][1]);
                $temp['rezerv'] = $rezerv->rezervList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/rezerv/rezervlist', TRUE);
                unset($temp,$rezerv);
                break;
//-------------------------------------------------Упрвление отзывами----------------------------------------------------
           
            case 'reviewlist':
                require_once MODULES.'admin/models/reviewsmodel.class.inc';
                $review = new reviewmodel();
                $temp['review'] = $review->reviewsList();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/reviews/reviewslist', TRUE);
                unset($temp,$review);
                break;
            case 'editreview':
                require_once MODULES.'admin/models/reviewsmodel.class.inc';
                $review = new reviewmodel();
               
                if($_POST):
                   $review->updateReview($param['params'][1]);
                endif;
                
                $temp = $review->getReviewInfo($param['params'][1]); 
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/reviews/editreviewform', TRUE);
                unset($temp,$review);
                break;
            case 'dellreview';
                require_once MODULES.'admin/models/reviewsmodel.class.inc';
                $review = new reviewmodel();
                
                $review->dellReview($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/reviewlist");
                break;
//-------------------------------------------------Упрвление баннерами----------------------------------------------------
            case 'bannerlist':
                require_once MODULES.'admin/models/bannersmodel.class.inc';
                $banner = new bannersmodel();
                $temp['banner'] = $banner->getBanners();
               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/banners/bannerlist', TRUE);
                unset($temp,$banner);
                break;
            case 'addbanner':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/bannersmodel.class.inc';
                $banner = new bannersmodel();
                
                if($_POST):
                    $banner->createBanner();
                endif;
                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/banners/createbannreform', TRUE);
                unset($temp,$banner);
                break;
            case 'dellbanner':
                require_once MODULES.'admin/models/bannersmodel.class.inc';
                $banner = new bannersmodel();
                $banner->dellBanner($param['params'][1]);                
                header("Location: ".BASEURL.LANG."/admin/bannerlist");
                break;
            case 'editbanner':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/bannersmodel.class.inc';
                $banner = new bannersmodel();
                
                if($_POST):
                    $banner->updateBanner($param['params'][1]);
                endif;
                $temp = $banner->getBannInfo($param['params'][1]);                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/banners/editbanner', TRUE);
                unset($temp,$banner);
                break;
//------------------------------------------------Методы для управления магазином-----------------------------------------
            case 'catlist':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                if($param['params'][1]=='up'):
                    $catalog->sortUp($param['params'][2]);
                    $param['params'][1] ='';
                elseif($param['params'][1]=='dwn'):    
                    $catalog->sortDwn($param['params'][2]);
                    $param['params'][1]='';
                endif;
                
                $temp['grplist'] =  $catalog->getGroupList();
                $temp['prodlist'] = $catalog->getProducts($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/catlist', TRUE);
                unset($temp,$catalog);
                break;
            case 'addprod':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                if($_POST):
                    $catalog->addProduct();
                endif;
                $temp['lang'] = $catalog->getLang();
                $temp['grplist'] =  $catalog->getGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/addprodform', TRUE);
                unset($temp,$catalog);
                break;
            case 'addgrp':     
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                if($_POST):                    
                    $catalog->addGroup();
                    header("Location: ".BASEURL.LANG."admin/catlist");                
                endif;
                
                $temp['lang'] = $catalog->getLang();
                $temp['grplist'] =  $catalog->getGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/addgrpform', TRUE);                
                unset($temp,$catalog);
                break;
            case 'editgroup':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                if($_POST):
                   $catalog->updateGroup($param['params'][1]); 
                endif;
                
                if($param['params'][2]=='on'):
                    $catalog->attachPropGroup($param['params'][3], $param['params'][1]);
                elseif($param['params'][2]=='off'):    
                    $catalog->detachPropGroup($param['params'][3], $param['params'][1]);
                endif;
                
                if($this->_module_exist('catalogue_property')):
                    $temp['proplist'] = $catalog->getPropForGroup(); 
                endif;
                
                $temp['lang'] = $catalog->getLang();
                $temp['grpinfo'] = $catalog->getGroupInfo($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/editgroup', TRUE);                
                unset($temp,$catalog);
                break;
            case 'dellgroup':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                $catalog->dellGroup($param['params'][1]);
                
                header("Location: ".BASEURL.LANG."/admin/catlist");
                unset($temp,$catalog);
                break;
            case 'editprod':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                
                if($_POST):
                    $catalog->updateProduct($param['params'][1]);
                endif;                
                
                if($param['params'][2]=='on'):
                    $catalog->detachPropItem($param['params'][3], $param['params'][1]);
                elseif($param['params'][2]=='off'):                    
                    $catalog->attachPropItem($param['params'][3], $param['params'][1]);
                endif;
                
                $temp['lang'] = $catalog->getLang();
                $temp['grplist'] =  $catalog->getGroupList();
                $temp['prodinfo'] = $catalog->getProdInfo($param['params'][1]);
                $temp['property_exc'] = $catalog->getItemProperty($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/editprod', TRUE);                
                unset($temp,$catalog);
                break;
            case 'dellprod':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                $catalog->dellProduct($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/catlist");
                unset($temp,$catalog);
                break;
//------------------------------------------------Управление свойствами товара-------------------------------------------
            case 'propertylist':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                $temp['proplist'] = $catalog->getPropertyList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/propertylist', TRUE);
                break;  
            case 'addpropgroup':
                if($_POST):
                    require_once MODULES.'admin/models/cataloguemodel.class.inc';
                    $catalog = new cataloguemodel();
                    $catalog->createPropGroup();
                    header("Location: ".BASEURL.LANG."admin/propertylist");
                endif;
                
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/addpropgroup', TRUE);
                break;
            case 'addproperty':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                if($_POST):
                    $catalog->createProperty();
                    header("Location: ".BASEURL.LANG."admin/propertylist");
                endif;
                
                $temp['proplist'] = $catalog->getPropGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/addproperty', TRUE);
                break;
            case 'dellpropgroup':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                $catalog->dellPropGrup($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/propertylist");
                break;
            case 'dellproperty':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                $catalog->dellProperty($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/propertylist");
                break;
            case 'editproperty':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                if($_POST):
                    $catalog->updateProperty($param['params'][1]);                    
                endif;
                
                $temp['grouplist'] = $catalog->getPropGroupList();
                 $temp['propinfo'] = $catalog->getPropertyInfo($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/editproperty', TRUE);
                break;
            case 'editpropgroup':
                require_once MODULES.'admin/models/cataloguemodel.class.inc';
                $catalog = new cataloguemodel();
                if($_POST):                    
                    $catalog->updatePopGroup($param['params'][1]);                 
                endif;
                $temp['groupinfo'] = $catalog->propGroupInfo($param['params'][1]);               
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/catalogue/editpropgroup', TRUE);
                break;
//-------------------------------------------------Модуль упрвления заказами ---------------------------------------------
            case 'orderlist':
                require_once MODULES.'admin/models/cartmodel.class.inc';
                $cart = new cartmodel();
                
                $temp['orderlist'] = $cart->getOrderList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/cart/orderlist', TRUE);
                 unset($temp,$cart);
                break;
            case 'dellorder':
                require_once MODULES.'admin/models/cartmodel.class.inc';
                $cart = new cartmodel();                
                $cart->dellOrder($param['params'][1]);                
                unset($cart);
                header("Location: ".BASEURL.LANG."admin/orderlist");                
                break;
            case 'vieworder':
                require_once MODULES.'admin/models/cartmodel.class.inc';
                $cart = new cartmodel();
                if($param['params'][2]):
                    $cart->changeStatus($param['params'][1],$param['params'][2]);
                endif;
                
                $temp['cat_page'] = $cart->getCatPage();
                $temp['ord_info'] = $cart->getOrder($param['params'][1]);
                $temp['statuslist'] = $cart->getStatusList(); 
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/cart/orderinfo', TRUE);
                unset($temp,$cart);
                break;
//-------------------------------------------------Модуль управления кабинетом пользователя ------------------------------
            case 'officeuserlist':
                require_once MODULES.'admin/models/officemodel.class.inc';
                $office = new officemodel();
                $temp['officeusers'] = $office->getOfficeUserList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/office/userlist', TRUE);
                unset($temp,$cart); 
                break;
//-------------------------------------------------Модуль управления Информацией(Акции,Обьявления,Новости)-------------------
            case 'infoblocklist':
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST):
                    $infoblock->addInfoblock();
                endif;
                
                $temp['infoblock'] = $infoblock->infoblocksList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/infoblocklist', TRUE);
                unset($temp,$infoblock);
                break;
            case 'infgrplist':
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($param['params'][1]=='up'):
                    $catalog->sortUp($param['params'][2]);
                    $param['params'][1] ='';
                elseif($param['params'][1]=='dwn'):    
                    $catalog->sortDwn($param['params'][2]);
                    $param['params'][1]='';
                endif;
               
                $temp['grplist'] = $infoblock->getGroupList();
                $temp['prodlist'] = $infoblock->getListUnit($param['params'][2],$param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/groupinflist', TRUE);
                break;
            case 'addinfrubric':
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST):
                    $infoblock->addRubric();
                    header("Location: ".BASEURL.LANG."admin/infgrplist");
                endif;
                  
                $temp['grplist'] =  $infoblock->getGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/addinfrubric', TRUE);
                break;
            case 'addinfunit':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST['unit']):                    
                    $infoblock->addUnitInfo();                
                endif;
                
                $temp['branch'] = $infoblock->getInfBranch(); 
                $temp['grplist'] =  $infoblock->getGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/addinfunit', TRUE);
                break;
            case 'dellinfunit':
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                $infoblock->dellInfUnit($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/infgrplist");
                break;
            case 'dellinfgroup':
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                $infoblock->dellInfGroup($param['params'][1]);
                header("Location: ".BASEURL.LANG."admin/infgrplist");               
                break;
            case 'editinfunit':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST):
                    $infoblock->updateUnit($param['params'][1]);
                endif;
                
                $temp = $infoblock->getUnitInfo($param['params'][1]); 
                $temp['branch'] = $infoblock->getInfBranch(); 
                $temp['grplist'] =  $infoblock->getGroupList();
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/editinfunit', TRUE);
                break;
            case 'editinfgroup':    
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                if($_POST):
                    $infoblock->upadteInfGroup($param['params'][1]);
                endif;
                $temp = $infoblock->getInfGroupInfo($param['params'][1]);
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/editinfrubric', TRUE);
                break;
            case 'addinfstock': 
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST['unit']):                    
                    $infoblock->addUnitInfo();                
                endif;               
             
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/addinfstock', TRUE);
                break;
            case 'addinfnews':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST['unit']):                    
                    $infoblock->addUnitInfo();                
                endif;               
             
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/addinfnews', TRUE);
                break;
            case 'addinfarticle':
                require_once MODULES.'admin/models/resizemodel.class.inc';
                require_once MODULES.'admin/models/infoblockmodel.class.inc';
                $infoblock = new infoblockmodel();
                
                if($_POST['unit']):                    
                    $infoblock->addUnitInfo();                
                endif;               
             
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/admin/infoblock/addinfarticle', TRUE);
                break;        
//-------------------------------------------------Вывод по умолчанию--- доджна быть общая статистика---------------------
                
            default:
                $data.= 'Внутренний контент админки... по дефолту...';
                break;
        endswitch;
        
        unset($auth); 
        return $data;
    }
    /*
     * Метод который обрабатывает редактирование
     * конкретных блоков
     */
    private function _blockEdit($module,$param){
        $model = $module.'model';
        require_once MODULES.'admin/models/'.$model.'.class.inc';
        $block = new $model();
        $blocks['block'] = $block->blocks($param);
        $blocks['param'] = $param;        
                
        $data = Display::view($blocks, 'modules/'.LANGDIR.'/admin/'.$module.'/'.$module.'block', TRUE);
        
        return $data;
    }
    private function _module_exist($module){
        $module = db::GetOne("SELECT id FROM module WHERE name='{$module}'");
        if($module):
            return TRUE;
        else:    
            return FALSE;
        endif;
    }
  }
?>