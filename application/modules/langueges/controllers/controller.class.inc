<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of controllres
 *
 * @author Alex
 */
class langueges {
    
    public function displayModule($view,$vid=NULL,$param=NULL,$file){
      
        $data = FALSE;
      
        switch($view):
            case '1':
                require_once MODULES.'langueges/models/languegesmodel.class.inc';
                $lang = new languegesmodel();
               
                $temp['langs'] = $lang->getLang();
                $temp['selected_page'] = $param['pagename'];               
                $temp['sel_params'] = $param['params'];                
                break;
            
        endswitch;
        $data.= Display::view($temp, 'modules/'.LANGDIR.'/langueges/lang_'.$view.'_'.$file,TRUE);            
        return $data;
    }    
}

?>
