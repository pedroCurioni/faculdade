import os

from langchain_community.embeddings import HuggingFaceEmbeddings
from langchain_community.vectorstores.chroma import Chroma
from langchain_core.output_parsers import StrOutputParser
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.runnables import RunnablePassthrough
from langchain_google_genai import ChatGoogleGenerativeAI
from langchain_text_splitters import RecursiveCharacterTextSplitter

from loaders import pdf_ocr_loader

os.environ["GOOGLE_API_KEY"] = "AIzaSyCygtIW02iiuLHYDcgpPrzpK6-GOir97rQ"

file_path = "MAE004.pdf"

embeddings = HuggingFaceEmbeddings(model_name="intfloat/multilingual-e5-large-instruct")
text_splitter = RecursiveCharacterTextSplitter(
    chunk_size=1024,
    chunk_overlap=128,
)

document = pdf_ocr_loader(file_path)
print("Document Loaded")
document_splits = text_splitter.split_documents(document)
print("Document Splitteed")
# document = PyPDFLoader(file_path).load_and_split(text_splitter)

vector_store = Chroma.from_documents(document_splits, embedding=embeddings)
print("Vector store created")
model = ChatGoogleGenerativeAI(model="gemini-pro", temperature=1)

template = """Responda a pergunta baseada no contexto a seguir e em noções basicas de eletrodinamica:
{context}

Question: {pergunta}
"""
prompt = ChatPromptTemplate.from_template(template)

chain = (
    {
        "context": vector_store.as_retriever(search_kwargs={"k": 20}),
        "pergunta": RunnablePassthrough(),
    }
    | prompt
    | model
    | StrOutputParser()
)

while True:
    pergunta = input("Pergunta: ")
    resposta = chain.invoke(pergunta)
    print(f"Resposta: {resposta}")
