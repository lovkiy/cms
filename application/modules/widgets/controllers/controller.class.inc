<?php


/**
 * Description of controller
 *
 * @author Alex
 */
class widgets {
    
    public function displayModule($view,$vid=NULL,$param=NULL){
        
        $data = FALSE;
        
        $lang_id = db::GetOne("SELECT id FROM languages WHERE code='".LANGDIR."'");
       
        $query = db::GetALL("SELECT w.content FROM widgets w 
                             JOIN pages_views pv ON pv.block_id=w.id
                             WHERE pv.p_id={$param['page']} 
                                 AND pv.l_id={$vid} AND pv.lang_id={$lang_id}");
        
        for($x=0;$x<sizeof($query);$x++):
            $data.=$query[$x]['content'];
        endfor;                     
                             
        return $data;
    }
}

?>
