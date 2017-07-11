<?php

/**
 * Description of textmodel
 *
 * @author Alex
 */
class textmodel {
    
     final public function getText($page,$l_id,$lang_id){
        
        $query = db::GetAll("SELECT t.description FROM text t 
                             JOIN pages_views pv ON pv.block_id = t.id
                             WHERE pv.p_id={$page} 
                                 AND pv.l_id = {$l_id}
                                 AND pv.lang_id={$lang_id}");
        if($query):
            return $query[0]['description'];
        endif;
     }
}

?>
