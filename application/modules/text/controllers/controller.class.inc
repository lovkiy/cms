<?php

/**
 * Description of controllres
 *
 * @author Alex
 */
class text {
    
    public function displayModule($view,$vid=NULL,$param=NULL,$file,$module_name){
     
        $data = FALSE;
        $lang_id = db::GetOne("SELECT id FROM languages WHERE code='".LANGDIR."'");    
        
        switch($view):
            case '1':
                require_once MODULES.'text/models/textmodel.class.inc';
                $text = new textmodel();
             
                $temp['text']= $text->getText($param['page'], $vid,$lang_id);                
                break;            
        endswitch;
        $data.= Display::view($temp,'modules/'.LANGDIR.'/'.$module_name.'/'.$module_name.'_'.$view.'_'.$file,TRUE);    
        return $data;
    }    
}

?>
