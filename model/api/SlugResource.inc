<?php
	abstract class SlugResource extends Resource{
		/** @String */
		protected $slug;
		
		public function __construct(){
			call_user_func_array(array("parent","__construct"),func_get_args());
			
			if(!$this->getSlug()){
				$this->setSlug($this->getId());
			}
		}
		
		/*
		 * Ensure that the object's slug is unique
		 */
		protected function reconcileSlug(){
			$counter = 1;
			$originalSlug = $this->getSlug();
			
			if(DatabaseAdministrator::tableExists(get_class($this))){
				while(DatabaseAdministrator::execute("SELECT * FROM ".get_class($this)." AS child JOIN SlugResource AS parent ON child.id = parent.id".
									" WHERE child.id != ? AND parent.slug = ?",$this->getId(),$this->getSlug())){
					$this->setSlug($originalSlug.$counter);
					$counter++;
				}
			}
		}
	}
?>