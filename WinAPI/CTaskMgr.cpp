#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}

void CTaskMgr::Tick()
{
	// Dead 오브젝트 처리
	for (size_t i = 0; i < m_Garbage.size(); ++i)
	{
		delete m_Garbage[i];
	}
	m_Garbage.clear();


	for (size_t i = 0; i < m_Task.size(); ++i)
	{
		switch (m_Task[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;			
			LAYER_TYPE Type = (LAYER_TYPE)m_Task[i].Param1;
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject, Type);
			pObject->Begin();
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;

			// Dead 처리가 안된 경우에만 처리해준다. 
			// 동시에 같은 오브젝트에 대해서 Delete 요청이 여러번인 경우 대처하기 위함
			if (!pObject->IsDead())
			{
				pObject->m_Dead = true;
				m_Garbage.push_back(pObject);
			}
		}
			break;
		case TASK_TYPE::CHANGE_LEVEL:
		{
			LEVEL_TYPE eNextLevel = (LEVEL_TYPE)m_Task[i].Param0;
			CLevelMgr::GetInst()->ChangeLevel(eNextLevel);
		}

			break;	
		}
	}

	m_Task.clear();
}