<?php

/**
 * Description of layoutsmodel
 *
 * @author Alex
 */

class layoutsmodel {
    
    final public function layoutList(){
        $query = db::GetAll("SELECT * FROM templates WHERE id!=1 ");       
        return $query;
    }    
    final public function templateList(){
        
        $layout = APP."templates/layouts/".LANGDIR."/";
        
        foreach (glob($layout."*.tpl") as $filename) {
            $filename =  substr($filename, 0,strlen($filename)-4);
            $filename = substr($filename,  strlen($layout),strlen($filename)-strlen($layout));
            $file[] = $filename;
        } 
        $admin =  array_shift($file);
        return $file;
    }
    final public function createLayout($post){
        
        
        $name = db::quote($_POST['layout_name']);
        $template = $_POST['layout'];
        db::execute("INSERT INTO templates (name,template) VALUES (".$name.",'".$template."')");
       
        $layout_id = db::lastInsertId();       
        return $layout_id;
    }
    final public function genLable($tpl_id){       
        
       // $tpl = db::GetOne("SELECT template FROM templates WHERE id={$layout_id}");
     
        for($x=1;$x<100;$x++): 
            $module = db::GetAll("SELECT mv.name,l.id,t.name as layout FROM module_views mv
                                  JOIN layouts l ON l.mv_id=mv.id 
                                  JOIN templates t ON t.id=l.template
                                  WHERE t.id=".$tpl_id." AND l.block=".$x);
            
      
            if($module[0]['name']):
                $views='';
                foreach ($module as $key=>$val):
                    $views.= $val['name']."  
                        <b>Сорт.</b>   
                        <b>
                            <a href='".BASEURL.LANG."admin/dellview/{$tpl_id}/{$val['id']}'>Уд.</a>
                        </b>
                        <br />";
                endforeach;
                $lable['block'.$x] = $views."<a href='".BASEURL.LANG."admin/addblock/{$tpl_id}/{$x}'>+ в блок ".$x."</a><br />";
            else:
                $lable['block'.$x] = "<a href='".BASEURL.LANG."admin/addblock/{$tpl_id}/{$x}'>+ в блок ".$x."</a><br />"; 
            endif;
            
        endfor;
        return $lable;
    }
    final public function delLayout($layout_id){
        
        $pid = db::GetAll("SELECT id FROM pages WHERE temp_id={$layout_id}");
        for($x=0;$x<sizeof($pid);$x++):
            db::execute("DELETE FROM pages_views WHERE p_id={$pid[$x]['id']}");
            db::execute("DELETE FROM pages WHERE id={$pid[$x]['id']}");
        endfor;
        
        db::execute("DELETE FROM layouts WHERE template ={$layout_id}");        
        db::execute("DELETE FROM templates WHERE id=".$layout_id);       
    }
    public function getModulelist(){        
        $query = db::GetAll("SELECT * FROM module WHERE id!=1");
        return $query;
    }
    public function  getViewslist($module){
    
        $query = db::GetAll("SELECT * FROM module_views WHERE module=".$module);
        return $query;
    }
    public function editLayout($post){
            
       db::execute("INSERT INTO layouts (template,block,mm,mv_id,file_id,description) 
                    VALUES ({$post['tplname']},{$post['block']},{$post['module']},{$post['view']},".$post['file_id'][$post['view']].",".db::quote($post['description']).")");
       $insId = db::lastInsertId();
       
       if($insId):
           return "Блок долбавлен к шаблону";
       else:
           return "Невозможно обработать заданный запросс...";
       endif;        
    }
    public function getTpl($tpl_id){
        $tpl = db::GetOne("SELECT template FROM templates WHERE id={$tpl_id}");
        return $tpl;
    }
    public function getViewsFiles($module_id){
        
        $module_name = db::GetOne("SELECT name FROM module WHERE id = {$module_id}");
        $path = APP."templates/modules/".LANGDIR."/".$module_name;
        foreach (glob($path."/*".EXT) as $filename) {            
         //   echo "$filename size " . filesize($filename) . "\n";
            $temp_arr = explode('_', $filename);
            $file_name = explode("/",$filename);
           
            $files[$temp_arr[1]][rtrim($temp_arr[2],EXT)] = $file_name[(sizeof($file_name)-1)];
        }
       return $files;
    }
    public function dellView($l_id){
        db::execute("DELETE FROM layouts WHERE id={$l_id}");
        db::execute("DELETE FROM pages_views WHERE l_id = {$l_id}");
    }
    
}

?>
