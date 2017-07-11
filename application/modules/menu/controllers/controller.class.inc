<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of controller
 *
 * @author Alex
 */
class menu {
    /*
     * TODO: переписать класс, нужно также переписать добавление менюхи
     * пока он наполовину рабочий...
     */
    public function displayModule($view,$vid=NULL,$param=NULL){
        
		
		
       require_once MODULES.'menu/models/menumodel.class.inc';
       $menu = new menumodel();
       
       $data = FALSE;
       $lang_id = db::GetOne("SELECT id FROM languages WHERE code='".LANGDIR."'");
      
       switch($view):
            case '1':
                $temp['menu'] = $menu->showMenu($param['page'],$vid,$lang_id);              
                $temp['page'] = $param['pagename'];
                $data.= Display::view($temp, 'modules/'.LANGDIR.'/menu/menu',TRUE);
                break;
            
        endswitch;
        
        return $data;
    }
}

?>
